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
struct dlm_ls {char* ls_name; void* ls_debug_waiters_dentry; void* ls_debug_toss_dentry; void* ls_debug_all_dentry; void* ls_debug_locks_dentry; void* ls_debug_rsb_dentry; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int DLM_LOCKSPACE_LEN ; 
 int S_IFREG ; 
 int S_IRUGO ; 
 void* debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct dlm_ls*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlm_root ; 
 int /*<<< orphan*/  format1_fops ; 
 int /*<<< orphan*/  format2_fops ; 
 int /*<<< orphan*/  format3_fops ; 
 int /*<<< orphan*/  format4_fops ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  waiters_fops ; 

void dlm_create_debug_file(struct dlm_ls *ls)
{
	char name[DLM_LOCKSPACE_LEN + 8];

	/* format 1 */

	ls->ls_debug_rsb_dentry = debugfs_create_file(ls->ls_name,
						      S_IFREG | S_IRUGO,
						      dlm_root,
						      ls,
						      &format1_fops);

	/* format 2 */

	memset(name, 0, sizeof(name));
	snprintf(name, DLM_LOCKSPACE_LEN + 8, "%s_locks", ls->ls_name);

	ls->ls_debug_locks_dentry = debugfs_create_file(name,
							S_IFREG | S_IRUGO,
							dlm_root,
							ls,
							&format2_fops);

	/* format 3 */

	memset(name, 0, sizeof(name));
	snprintf(name, DLM_LOCKSPACE_LEN + 8, "%s_all", ls->ls_name);

	ls->ls_debug_all_dentry = debugfs_create_file(name,
						      S_IFREG | S_IRUGO,
						      dlm_root,
						      ls,
						      &format3_fops);

	/* format 4 */

	memset(name, 0, sizeof(name));
	snprintf(name, DLM_LOCKSPACE_LEN + 8, "%s_toss", ls->ls_name);

	ls->ls_debug_toss_dentry = debugfs_create_file(name,
						       S_IFREG | S_IRUGO,
						       dlm_root,
						       ls,
						       &format4_fops);

	memset(name, 0, sizeof(name));
	snprintf(name, DLM_LOCKSPACE_LEN + 8, "%s_waiters", ls->ls_name);

	ls->ls_debug_waiters_dentry = debugfs_create_file(name,
							  S_IFREG | S_IRUGO,
							  dlm_root,
							  ls,
							  &waiters_fops);
}