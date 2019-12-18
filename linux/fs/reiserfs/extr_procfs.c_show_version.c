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
struct super_block {int dummy; } ;
struct seq_file {struct super_block* private; } ;
struct TYPE_2__ {int s_properties; } ;

/* Variables and functions */
 int REISERFS_3_5 ; 
 int REISERFS_3_6 ; 
 TYPE_1__* REISERFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*,char*) ; 

__attribute__((used)) static int show_version(struct seq_file *m, void *unused)
{
	struct super_block *sb = m->private;
	char *format;

	if (REISERFS_SB(sb)->s_properties & (1 << REISERFS_3_6)) {
		format = "3.6";
	} else if (REISERFS_SB(sb)->s_properties & (1 << REISERFS_3_5)) {
		format = "3.5";
	} else {
		format = "unknown";
	}

	seq_printf(m, "%s format\twith checks %s\n", format,
#if defined( CONFIG_REISERFS_CHECK )
		   "on"
#else
		   "off"
#endif
	    );
	return 0;
}