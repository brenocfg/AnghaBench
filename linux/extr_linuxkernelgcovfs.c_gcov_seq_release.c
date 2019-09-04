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
struct seq_file {struct gcov_iterator* private; } ;
struct inode {int dummy; } ;
struct gcov_iterator {int dummy; } ;
struct gcov_info {int dummy; } ;
struct file {struct seq_file* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  gcov_info_free (struct gcov_info*) ; 
 int /*<<< orphan*/  gcov_iter_free (struct gcov_iterator*) ; 
 struct gcov_info* gcov_iter_get_info (struct gcov_iterator*) ; 
 int /*<<< orphan*/  seq_release (struct inode*,struct file*) ; 

__attribute__((used)) static int gcov_seq_release(struct inode *inode, struct file *file)
{
	struct gcov_iterator *iter;
	struct gcov_info *info;
	struct seq_file *seq;

	seq = file->private_data;
	iter = seq->private;
	info = gcov_iter_get_info(iter);
	gcov_iter_free(iter);
	gcov_info_free(info);
	seq_release(inode, file);

	return 0;
}