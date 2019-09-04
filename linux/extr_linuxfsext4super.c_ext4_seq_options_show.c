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
struct super_block {int dummy; } ;
struct seq_file {struct super_block* private; } ;

/* Variables and functions */
 int _ext4_show_options (struct seq_file*,struct super_block*,int) ; 
 scalar_t__ sb_rdonly (struct super_block*) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

int ext4_seq_options_show(struct seq_file *seq, void *offset)
{
	struct super_block *sb = seq->private;
	int rc;

	seq_puts(seq, sb_rdonly(sb) ? "ro" : "rw");
	rc = _ext4_show_options(seq, sb, 1);
	seq_puts(seq, "\n");
	return rc;
}