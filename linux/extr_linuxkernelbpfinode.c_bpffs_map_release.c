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
struct seq_file {int dummy; } ;
struct inode {int dummy; } ;
struct file {struct seq_file* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  map_iter (struct seq_file*) ; 
 int /*<<< orphan*/  map_iter_free (int /*<<< orphan*/ ) ; 
 int seq_release (struct inode*,struct file*) ; 

__attribute__((used)) static int bpffs_map_release(struct inode *inode, struct file *file)
{
	struct seq_file *m = file->private_data;

	map_iter_free(map_iter(m));

	return seq_release(inode, file);
}