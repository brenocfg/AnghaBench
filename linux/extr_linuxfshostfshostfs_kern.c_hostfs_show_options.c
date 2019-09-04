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
struct seq_file {int dummy; } ;
struct dentry {TYPE_1__* d_sb; } ;
struct TYPE_2__ {char* s_fs_info; } ;

/* Variables and functions */
 scalar_t__ append ; 
 char const* root_ino ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 int /*<<< orphan*/  seq_show_option (struct seq_file*,char const*,int /*<<< orphan*/ *) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static int hostfs_show_options(struct seq_file *seq, struct dentry *root)
{
	const char *root_path = root->d_sb->s_fs_info;
	size_t offset = strlen(root_ino) + 1;

	if (strlen(root_path) > offset)
		seq_show_option(seq, root_path + offset, NULL);

	if (append)
		seq_puts(seq, ",append");

	return 0;
}