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
typedef  scalar_t__ u32 ;
struct inode_security_struct {scalar_t__ sid; } ;
struct inode {int dummy; } ;
struct file_security_struct {scalar_t__ sid; scalar_t__ isid; scalar_t__ pseqno; } ;
struct file {int dummy; } ;

/* Variables and functions */
 scalar_t__ avc_policy_seqno (int /*<<< orphan*/ *) ; 
 scalar_t__ current_sid () ; 
 struct inode* file_inode (struct file*) ; 
 struct inode_security_struct* inode_security (struct inode*) ; 
 struct file_security_struct* selinux_file (struct file*) ; 
 int selinux_revalidate_file_permission (struct file*,int) ; 
 int /*<<< orphan*/  selinux_state ; 

__attribute__((used)) static int selinux_file_permission(struct file *file, int mask)
{
	struct inode *inode = file_inode(file);
	struct file_security_struct *fsec = selinux_file(file);
	struct inode_security_struct *isec;
	u32 sid = current_sid();

	if (!mask)
		/* No permission to check.  Existence test. */
		return 0;

	isec = inode_security(inode);
	if (sid == fsec->sid && fsec->isid == isec->sid &&
	    fsec->pseqno == avc_policy_seqno(&selinux_state))
		/* No change since file_open check. */
		return 0;

	return selinux_revalidate_file_permission(file, mask);
}