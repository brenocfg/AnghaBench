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
typedef  union fscrypt_context {int dummy; } fscrypt_context ;
struct inode {TYPE_2__* i_sb; int /*<<< orphan*/  i_crypt_info; } ;
struct fscrypt_info {int /*<<< orphan*/  ci_policy; } ;
typedef  int /*<<< orphan*/  ctx ;
struct TYPE_4__ {TYPE_1__* s_cop; } ;
struct TYPE_3__ {int (* set_context ) (struct inode*,union fscrypt_context*,int,void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int ENOKEY ; 
 int FSCRYPT_SET_CONTEXT_MAX_SIZE ; 
 struct fscrypt_info* READ_ONCE (int /*<<< orphan*/ ) ; 
 int fscrypt_get_encryption_info (struct inode*) ; 
 int fscrypt_new_context_from_policy (union fscrypt_context*,int /*<<< orphan*/ *) ; 
 int stub1 (struct inode*,union fscrypt_context*,int,void*) ; 

int fscrypt_inherit_context(struct inode *parent, struct inode *child,
						void *fs_data, bool preload)
{
	union fscrypt_context ctx;
	int ctxsize;
	struct fscrypt_info *ci;
	int res;

	res = fscrypt_get_encryption_info(parent);
	if (res < 0)
		return res;

	ci = READ_ONCE(parent->i_crypt_info);
	if (ci == NULL)
		return -ENOKEY;

	ctxsize = fscrypt_new_context_from_policy(&ctx, &ci->ci_policy);

	BUILD_BUG_ON(sizeof(ctx) != FSCRYPT_SET_CONTEXT_MAX_SIZE);
	res = parent->i_sb->s_cop->set_context(child, &ctx, ctxsize, fs_data);
	if (res)
		return res;
	return preload ? fscrypt_get_encryption_info(child): 0;
}