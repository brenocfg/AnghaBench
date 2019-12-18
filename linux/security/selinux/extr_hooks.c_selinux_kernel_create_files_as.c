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
typedef  int /*<<< orphan*/  u32 ;
struct task_security_struct {int /*<<< orphan*/  create_sid; } ;
struct inode_security_struct {int /*<<< orphan*/  sid; } ;
struct inode {int dummy; } ;
struct cred {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERNEL_SERVICE__CREATE_FILES_AS ; 
 int /*<<< orphan*/  SECCLASS_KERNEL_SERVICE ; 
 int avc_has_perm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current_sid () ; 
 struct inode_security_struct* inode_security (struct inode*) ; 
 struct task_security_struct* selinux_cred (struct cred*) ; 
 int /*<<< orphan*/  selinux_state ; 

__attribute__((used)) static int selinux_kernel_create_files_as(struct cred *new, struct inode *inode)
{
	struct inode_security_struct *isec = inode_security(inode);
	struct task_security_struct *tsec = selinux_cred(new);
	u32 sid = current_sid();
	int ret;

	ret = avc_has_perm(&selinux_state,
			   sid, isec->sid,
			   SECCLASS_KERNEL_SERVICE,
			   KERNEL_SERVICE__CREATE_FILES_AS,
			   NULL);

	if (ret == 0)
		tsec->create_sid = isec->sid;
	return ret;
}