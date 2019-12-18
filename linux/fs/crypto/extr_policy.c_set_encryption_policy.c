#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  master_key_identifier; } ;
union fscrypt_policy {int version; TYPE_2__ v2; } ;
typedef  union fscrypt_context {int dummy; } fscrypt_context ;
struct inode {TYPE_3__* i_sb; } ;
struct TYPE_8__ {int /*<<< orphan*/  pid; int /*<<< orphan*/  comm; } ;
struct TYPE_7__ {TYPE_1__* s_cop; } ;
struct TYPE_5__ {int (* set_context ) (struct inode*,union fscrypt_context*,int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int EINVAL ; 
#define  FSCRYPT_POLICY_V1 129 
#define  FSCRYPT_POLICY_V2 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 TYPE_4__* current ; 
 int fscrypt_new_context_from_policy (union fscrypt_context*,union fscrypt_policy const*) ; 
 int /*<<< orphan*/  fscrypt_supported_policy (union fscrypt_policy const*,struct inode*) ; 
 int fscrypt_verify_key_added (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn_once (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct inode*,union fscrypt_context*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int set_encryption_policy(struct inode *inode,
				 const union fscrypt_policy *policy)
{
	union fscrypt_context ctx;
	int ctxsize;
	int err;

	if (!fscrypt_supported_policy(policy, inode))
		return -EINVAL;

	switch (policy->version) {
	case FSCRYPT_POLICY_V1:
		/*
		 * The original encryption policy version provided no way of
		 * verifying that the correct master key was supplied, which was
		 * insecure in scenarios where multiple users have access to the
		 * same encrypted files (even just read-only access).  The new
		 * encryption policy version fixes this and also implies use of
		 * an improved key derivation function and allows non-root users
		 * to securely remove keys.  So as long as compatibility with
		 * old kernels isn't required, it is recommended to use the new
		 * policy version for all new encrypted directories.
		 */
		pr_warn_once("%s (pid %d) is setting deprecated v1 encryption policy; recommend upgrading to v2.\n",
			     current->comm, current->pid);
		break;
	case FSCRYPT_POLICY_V2:
		err = fscrypt_verify_key_added(inode->i_sb,
					       policy->v2.master_key_identifier);
		if (err)
			return err;
		break;
	default:
		WARN_ON(1);
		return -EINVAL;
	}

	ctxsize = fscrypt_new_context_from_policy(&ctx, policy);

	return inode->i_sb->s_cop->set_context(inode, &ctx, ctxsize, NULL);
}