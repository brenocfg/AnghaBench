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
struct super_block {int /*<<< orphan*/  s_id; } ;
struct proc_dir_entry {int dummy; } ;
struct TYPE_2__ {struct proc_dir_entry* procdir; } ;

/* Variables and functions */
 int BDEVNAME_SIZE ; 
 TYPE_1__* REISERFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  proc_info_root ; 
 int /*<<< orphan*/  remove_proc_subtree (char*,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 

int reiserfs_proc_info_done(struct super_block *sb)
{
	struct proc_dir_entry *de = REISERFS_SB(sb)->procdir;
	if (de) {
		char b[BDEVNAME_SIZE];
		char *s;

		/* Some block devices use /'s */
		strlcpy(b, sb->s_id, BDEVNAME_SIZE);
		s = strchr(b, '/');
		if (s)
			*s = '!';

		remove_proc_subtree(b, proc_info_root);
		REISERFS_SB(sb)->procdir = NULL;
	}
	return 0;
}