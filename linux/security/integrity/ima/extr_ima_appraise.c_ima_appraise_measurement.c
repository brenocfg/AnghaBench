#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct modsig {int dummy; } ;
struct integrity_iint_cache {int flags; } ;
struct inode {int i_opflags; scalar_t__ i_size; TYPE_1__* i_sb; } ;
struct file {int f_mode; } ;
struct evm_ima_xattr_data {scalar_t__ type; } ;
struct dentry {int dummy; } ;
typedef  enum integrity_status { ____Placeholder_integrity_status } integrity_status ;
typedef  enum ima_hooks { ____Placeholder_ima_hooks } ima_hooks ;
struct TYPE_2__ {int s_iflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_INTEGRITY_DATA ; 
 int ENODATA ; 
 int ENOKEY ; 
 scalar_t__ EVM_IMA_XATTR_DIGSIG ; 
 int FMODE_CREATED ; 
 int IMA_APPRAISE_FIX ; 
 int IMA_DIGSIG_REQUIRED ; 
 int IMA_FAIL_UNVERIFIABLE_SIGS ; 
 int IMA_MODSIG_ALLOWED ; 
 int IMA_NEW_FILE ; 
 scalar_t__ IMA_XATTR_DIGEST_NG ; 
#define  INTEGRITY_FAIL 133 
#define  INTEGRITY_NOLABEL 132 
#define  INTEGRITY_NOXATTRS 131 
#define  INTEGRITY_PASS 130 
#define  INTEGRITY_PASS_IMMUTABLE 129 
#define  INTEGRITY_UNKNOWN 128 
 int IOP_XATTR ; 
 int SB_I_IMA_UNVERIFIABLE_SIGNATURE ; 
 int SB_I_UNTRUSTED_MOUNTER ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int) ; 
 int /*<<< orphan*/  XATTR_NAME_IMA ; 
 struct inode* d_backing_inode (struct dentry*) ; 
 int evm_verifyxattr (struct dentry*,int /*<<< orphan*/ ,struct evm_ima_xattr_data*,int,struct integrity_iint_cache*) ; 
 struct dentry* file_dentry (struct file*) ; 
 int ima_appraise ; 
 int /*<<< orphan*/  ima_cache_flags (struct integrity_iint_cache*,int) ; 
 int /*<<< orphan*/  ima_fix_xattr (struct dentry*,struct integrity_iint_cache*) ; 
 int /*<<< orphan*/  ima_set_cache_status (struct integrity_iint_cache*,int,int) ; 
 int /*<<< orphan*/  integrity_audit_msg (int /*<<< orphan*/ ,struct inode*,unsigned char const*,char const*,char const*,int,int /*<<< orphan*/ ) ; 
 int modsig_verify (int,struct modsig const*,int*,char const**) ; 
 int xattr_verify (int,struct integrity_iint_cache*,struct evm_ima_xattr_data*,int,int*,char const**) ; 

int ima_appraise_measurement(enum ima_hooks func,
			     struct integrity_iint_cache *iint,
			     struct file *file, const unsigned char *filename,
			     struct evm_ima_xattr_data *xattr_value,
			     int xattr_len, const struct modsig *modsig)
{
	static const char op[] = "appraise_data";
	const char *cause = "unknown";
	struct dentry *dentry = file_dentry(file);
	struct inode *inode = d_backing_inode(dentry);
	enum integrity_status status = INTEGRITY_UNKNOWN;
	int rc = xattr_len;
	bool try_modsig = iint->flags & IMA_MODSIG_ALLOWED && modsig;

	/* If not appraising a modsig, we need an xattr. */
	if (!(inode->i_opflags & IOP_XATTR) && !try_modsig)
		return INTEGRITY_UNKNOWN;

	/* If reading the xattr failed and there's no modsig, error out. */
	if (rc <= 0 && !try_modsig) {
		if (rc && rc != -ENODATA)
			goto out;

		cause = iint->flags & IMA_DIGSIG_REQUIRED ?
				"IMA-signature-required" : "missing-hash";
		status = INTEGRITY_NOLABEL;
		if (file->f_mode & FMODE_CREATED)
			iint->flags |= IMA_NEW_FILE;
		if ((iint->flags & IMA_NEW_FILE) &&
		    (!(iint->flags & IMA_DIGSIG_REQUIRED) ||
		     (inode->i_size == 0)))
			status = INTEGRITY_PASS;
		goto out;
	}

	status = evm_verifyxattr(dentry, XATTR_NAME_IMA, xattr_value, rc, iint);
	switch (status) {
	case INTEGRITY_PASS:
	case INTEGRITY_PASS_IMMUTABLE:
	case INTEGRITY_UNKNOWN:
		break;
	case INTEGRITY_NOXATTRS:	/* No EVM protected xattrs. */
		/* It's fine not to have xattrs when using a modsig. */
		if (try_modsig)
			break;
		/* fall through */
	case INTEGRITY_NOLABEL:		/* No security.evm xattr. */
		cause = "missing-HMAC";
		goto out;
	case INTEGRITY_FAIL:		/* Invalid HMAC/signature. */
		cause = "invalid-HMAC";
		goto out;
	default:
		WARN_ONCE(true, "Unexpected integrity status %d\n", status);
	}

	if (xattr_value)
		rc = xattr_verify(func, iint, xattr_value, xattr_len, &status,
				  &cause);

	/*
	 * If we have a modsig and either no imasig or the imasig's key isn't
	 * known, then try verifying the modsig.
	 */
	if (try_modsig &&
	    (!xattr_value || xattr_value->type == IMA_XATTR_DIGEST_NG ||
	     rc == -ENOKEY))
		rc = modsig_verify(func, modsig, &status, &cause);

out:
	/*
	 * File signatures on some filesystems can not be properly verified.
	 * When such filesystems are mounted by an untrusted mounter or on a
	 * system not willing to accept such a risk, fail the file signature
	 * verification.
	 */
	if ((inode->i_sb->s_iflags & SB_I_IMA_UNVERIFIABLE_SIGNATURE) &&
	    ((inode->i_sb->s_iflags & SB_I_UNTRUSTED_MOUNTER) ||
	     (iint->flags & IMA_FAIL_UNVERIFIABLE_SIGS))) {
		status = INTEGRITY_FAIL;
		cause = "unverifiable-signature";
		integrity_audit_msg(AUDIT_INTEGRITY_DATA, inode, filename,
				    op, cause, rc, 0);
	} else if (status != INTEGRITY_PASS) {
		/* Fix mode, but don't replace file signatures. */
		if ((ima_appraise & IMA_APPRAISE_FIX) && !try_modsig &&
		    (!xattr_value ||
		     xattr_value->type != EVM_IMA_XATTR_DIGSIG)) {
			if (!ima_fix_xattr(dentry, iint))
				status = INTEGRITY_PASS;
		}

		/* Permit new files with file signatures, but without data. */
		if (inode->i_size == 0 && iint->flags & IMA_NEW_FILE &&
		    xattr_value && xattr_value->type == EVM_IMA_XATTR_DIGSIG) {
			status = INTEGRITY_PASS;
		}

		integrity_audit_msg(AUDIT_INTEGRITY_DATA, inode, filename,
				    op, cause, rc, 0);
	} else {
		ima_cache_flags(iint, func);
	}

	ima_set_cache_status(iint, func, status);
	return status;
}