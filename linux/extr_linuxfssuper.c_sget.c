#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct user_namespace {int dummy; } ;
struct super_block {int dummy; } ;
struct file_system_type {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int /*<<< orphan*/  EPERM ; 
 struct super_block* ERR_PTR (int /*<<< orphan*/ ) ; 
 int SB_KERNMOUNT ; 
 int SB_SUBMOUNT ; 
 struct user_namespace* current_user_ns () ; 
 struct user_namespace init_user_ns ; 
 int /*<<< orphan*/  ns_capable (struct user_namespace*,int /*<<< orphan*/ ) ; 
 struct super_block* sget_userns (struct file_system_type*,int (*) (struct super_block*,void*),int (*) (struct super_block*,void*),int,struct user_namespace*,void*) ; 

struct super_block *sget(struct file_system_type *type,
			int (*test)(struct super_block *,void *),
			int (*set)(struct super_block *,void *),
			int flags,
			void *data)
{
	struct user_namespace *user_ns = current_user_ns();

	/* We don't yet pass the user namespace of the parent
	 * mount through to here so always use &init_user_ns
	 * until that changes.
	 */
	if (flags & SB_SUBMOUNT)
		user_ns = &init_user_ns;

	/* Ensure the requestor has permissions over the target filesystem */
	if (!(flags & (SB_KERNMOUNT|SB_SUBMOUNT)) && !ns_capable(user_ns, CAP_SYS_ADMIN))
		return ERR_PTR(-EPERM);

	return sget_userns(type, test, set, flags, user_ns, data);
}