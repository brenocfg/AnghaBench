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
struct inode_security_struct {int /*<<< orphan*/  sid; } ;
struct file_security_struct {int /*<<< orphan*/  pseqno; int /*<<< orphan*/  isid; } ;
struct file {int /*<<< orphan*/  f_cred; } ;

/* Variables and functions */
 int /*<<< orphan*/  avc_policy_seqno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 
 int file_path_has_perm (int /*<<< orphan*/ ,struct file*,int /*<<< orphan*/ ) ; 
 struct inode_security_struct* inode_security (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open_file_to_av (struct file*) ; 
 struct file_security_struct* selinux_file (struct file*) ; 
 int /*<<< orphan*/  selinux_state ; 

__attribute__((used)) static int selinux_file_open(struct file *file)
{
	struct file_security_struct *fsec;
	struct inode_security_struct *isec;

	fsec = selinux_file(file);
	isec = inode_security(file_inode(file));
	/*
	 * Save inode label and policy sequence number
	 * at open-time so that selinux_file_permission
	 * can determine whether revalidation is necessary.
	 * Task label is already saved in the file security
	 * struct as its SID.
	 */
	fsec->isid = isec->sid;
	fsec->pseqno = avc_policy_seqno(&selinux_state);
	/*
	 * Since the inode label or policy seqno may have changed
	 * between the selinux_inode_permission check and the saving
	 * of state above, recheck that access is still permitted.
	 * Otherwise, access might never be revalidated against the
	 * new inode label or new policy.
	 * This check is not redundant - do not remove.
	 */
	return file_path_has_perm(file->f_cred, file, open_file_to_av(file));
}