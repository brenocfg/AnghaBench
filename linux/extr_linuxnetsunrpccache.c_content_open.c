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
struct seq_file {struct cache_detail* private; } ;
struct inode {int dummy; } ;
struct file {struct seq_file* private_data; } ;
struct cache_detail {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int EACCES ; 
 int /*<<< orphan*/  cache_content_op ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int seq_open (struct file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int content_open(struct inode *inode, struct file *file,
			struct cache_detail *cd)
{
	struct seq_file *seq;
	int err;

	if (!cd || !try_module_get(cd->owner))
		return -EACCES;

	err = seq_open(file, &cache_content_op);
	if (err) {
		module_put(cd->owner);
		return err;
	}

	seq = file->private_data;
	seq->private = cd;
	return 0;
}