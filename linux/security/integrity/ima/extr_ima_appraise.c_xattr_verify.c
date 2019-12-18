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
struct integrity_iint_cache {int flags; TYPE_1__* ima_hash; int /*<<< orphan*/  atomic_flags; } ;
struct evm_ima_xattr_data {int type; int /*<<< orphan*/ * data; } ;
typedef  enum integrity_status { ____Placeholder_integrity_status } integrity_status ;
typedef  enum ima_hooks { ____Placeholder_ima_hooks } ima_hooks ;
struct TYPE_2__ {int length; int /*<<< orphan*/  digest; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_INTEGRITY_PLATFORM_KEYRING ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
#define  EVM_IMA_XATTR_DIGSIG 130 
 int /*<<< orphan*/  IMA_DIGSIG ; 
 int IMA_DIGSIG_REQUIRED ; 
#define  IMA_XATTR_DIGEST 129 
#define  IMA_XATTR_DIGEST_NG 128 
 int INTEGRITY_FAIL ; 
 int /*<<< orphan*/  INTEGRITY_KEYRING_IMA ; 
 int /*<<< orphan*/  INTEGRITY_KEYRING_PLATFORM ; 
 int INTEGRITY_PASS ; 
 int INTEGRITY_UNKNOWN ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int KEXEC_KERNEL_CHECK ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int integrity_digsig_verify (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ,int) ; 
 int memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int xattr_verify(enum ima_hooks func, struct integrity_iint_cache *iint,
			struct evm_ima_xattr_data *xattr_value, int xattr_len,
			enum integrity_status *status, const char **cause)
{
	int rc = -EINVAL, hash_start = 0;

	switch (xattr_value->type) {
	case IMA_XATTR_DIGEST_NG:
		/* first byte contains algorithm id */
		hash_start = 1;
		/* fall through */
	case IMA_XATTR_DIGEST:
		if (iint->flags & IMA_DIGSIG_REQUIRED) {
			*cause = "IMA-signature-required";
			*status = INTEGRITY_FAIL;
			break;
		}
		clear_bit(IMA_DIGSIG, &iint->atomic_flags);
		if (xattr_len - sizeof(xattr_value->type) - hash_start >=
				iint->ima_hash->length)
			/*
			 * xattr length may be longer. md5 hash in previous
			 * version occupied 20 bytes in xattr, instead of 16
			 */
			rc = memcmp(&xattr_value->data[hash_start],
				    iint->ima_hash->digest,
				    iint->ima_hash->length);
		else
			rc = -EINVAL;
		if (rc) {
			*cause = "invalid-hash";
			*status = INTEGRITY_FAIL;
			break;
		}
		*status = INTEGRITY_PASS;
		break;
	case EVM_IMA_XATTR_DIGSIG:
		set_bit(IMA_DIGSIG, &iint->atomic_flags);
		rc = integrity_digsig_verify(INTEGRITY_KEYRING_IMA,
					     (const char *)xattr_value,
					     xattr_len,
					     iint->ima_hash->digest,
					     iint->ima_hash->length);
		if (rc == -EOPNOTSUPP) {
			*status = INTEGRITY_UNKNOWN;
			break;
		}
		if (IS_ENABLED(CONFIG_INTEGRITY_PLATFORM_KEYRING) && rc &&
		    func == KEXEC_KERNEL_CHECK)
			rc = integrity_digsig_verify(INTEGRITY_KEYRING_PLATFORM,
						     (const char *)xattr_value,
						     xattr_len,
						     iint->ima_hash->digest,
						     iint->ima_hash->length);
		if (rc) {
			*cause = "invalid-signature";
			*status = INTEGRITY_FAIL;
		} else {
			*status = INTEGRITY_PASS;
		}
		break;
	default:
		*status = INTEGRITY_UNKNOWN;
		*cause = "unknown-ima-data";
		break;
	}

	return rc;
}