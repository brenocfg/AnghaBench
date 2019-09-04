#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct integrity_iint_cache {int flags; TYPE_1__* ima_hash; int /*<<< orphan*/  atomic_flags; } ;
struct inode {int i_opflags; scalar_t__ i_size; TYPE_2__* i_sb; } ;
struct file {int f_mode; } ;
struct evm_ima_xattr_data {int type; int /*<<< orphan*/ * digest; } ;
struct dentry {int dummy; } ;
typedef  enum integrity_status { ____Placeholder_integrity_status } integrity_status ;
typedef  enum ima_hooks { ____Placeholder_ima_hooks } ima_hooks ;
struct TYPE_4__ {int s_iflags; } ;
struct TYPE_3__ {int length; int /*<<< orphan*/  digest; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_INTEGRITY_DATA ; 
 int EINVAL ; 
 int ENODATA ; 
 int EOPNOTSUPP ; 
#define  EVM_IMA_XATTR_DIGSIG 136 
 int FMODE_CREATED ; 
 int IMA_APPRAISE_FIX ; 
 int /*<<< orphan*/  IMA_DIGSIG ; 
 int IMA_DIGSIG_REQUIRED ; 
 int IMA_FAIL_UNVERIFIABLE_SIGS ; 
 int IMA_NEW_FILE ; 
#define  IMA_XATTR_DIGEST 135 
#define  IMA_XATTR_DIGEST_NG 134 
#define  INTEGRITY_FAIL 133 
 int /*<<< orphan*/  INTEGRITY_KEYRING_IMA ; 
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
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct inode* d_backing_inode (struct dentry*) ; 
 int evm_verifyxattr (struct dentry*,int /*<<< orphan*/ ,struct evm_ima_xattr_data*,int,struct integrity_iint_cache*) ; 
 struct dentry* file_dentry (struct file*) ; 
 int ima_appraise ; 
 int /*<<< orphan*/  ima_cache_flags (struct integrity_iint_cache*,int) ; 
 int /*<<< orphan*/  ima_fix_xattr (struct dentry*,struct integrity_iint_cache*) ; 
 int /*<<< orphan*/  ima_set_cache_status (struct integrity_iint_cache*,int,int) ; 
 int /*<<< orphan*/  integrity_audit_msg (int /*<<< orphan*/ ,struct inode*,unsigned char const*,char const*,char const*,int,int /*<<< orphan*/ ) ; 
 int integrity_digsig_verify (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ,int) ; 
 int memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int ima_appraise_measurement(enum ima_hooks func,
			     struct integrity_iint_cache *iint,
			     struct file *file, const unsigned char *filename,
			     struct evm_ima_xattr_data *xattr_value,
			     int xattr_len)
{
	static const char op[] = "appraise_data";
	const char *cause = "unknown";
	struct dentry *dentry = file_dentry(file);
	struct inode *inode = d_backing_inode(dentry);
	enum integrity_status status = INTEGRITY_UNKNOWN;
	int rc = xattr_len, hash_start = 0;

	if (!(inode->i_opflags & IOP_XATTR))
		return INTEGRITY_UNKNOWN;

	if (rc <= 0) {
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
	case INTEGRITY_NOLABEL:		/* No security.evm xattr. */
		cause = "missing-HMAC";
		goto out;
	case INTEGRITY_FAIL:		/* Invalid HMAC/signature. */
		cause = "invalid-HMAC";
		goto out;
	default:
		WARN_ONCE(true, "Unexpected integrity status %d\n", status);
	}

	switch (xattr_value->type) {
	case IMA_XATTR_DIGEST_NG:
		/* first byte contains algorithm id */
		hash_start = 1;
		/* fall through */
	case IMA_XATTR_DIGEST:
		if (iint->flags & IMA_DIGSIG_REQUIRED) {
			cause = "IMA-signature-required";
			status = INTEGRITY_FAIL;
			break;
		}
		clear_bit(IMA_DIGSIG, &iint->atomic_flags);
		if (xattr_len - sizeof(xattr_value->type) - hash_start >=
				iint->ima_hash->length)
			/* xattr length may be longer. md5 hash in previous
			   version occupied 20 bytes in xattr, instead of 16
			 */
			rc = memcmp(&xattr_value->digest[hash_start],
				    iint->ima_hash->digest,
				    iint->ima_hash->length);
		else
			rc = -EINVAL;
		if (rc) {
			cause = "invalid-hash";
			status = INTEGRITY_FAIL;
			break;
		}
		status = INTEGRITY_PASS;
		break;
	case EVM_IMA_XATTR_DIGSIG:
		set_bit(IMA_DIGSIG, &iint->atomic_flags);
		rc = integrity_digsig_verify(INTEGRITY_KEYRING_IMA,
					     (const char *)xattr_value, rc,
					     iint->ima_hash->digest,
					     iint->ima_hash->length);
		if (rc == -EOPNOTSUPP) {
			status = INTEGRITY_UNKNOWN;
		} else if (rc) {
			cause = "invalid-signature";
			status = INTEGRITY_FAIL;
		} else {
			status = INTEGRITY_PASS;
		}
		break;
	default:
		status = INTEGRITY_UNKNOWN;
		cause = "unknown-ima-data";
		break;
	}

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
		if ((ima_appraise & IMA_APPRAISE_FIX) &&
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