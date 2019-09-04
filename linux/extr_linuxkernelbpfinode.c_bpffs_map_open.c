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
struct seq_file {struct map_iter* private; } ;
struct map_iter {int dummy; } ;
struct inode {struct bpf_map* i_private; } ;
struct file {struct seq_file* private_data; } ;
struct bpf_map {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  bpffs_map_seq_ops ; 
 struct map_iter* map_iter_alloc (struct bpf_map*) ; 
 int /*<<< orphan*/  map_iter_free (struct map_iter*) ; 
 int seq_open (struct file*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bpffs_map_open(struct inode *inode, struct file *file)
{
	struct bpf_map *map = inode->i_private;
	struct map_iter *iter;
	struct seq_file *m;
	int err;

	iter = map_iter_alloc(map);
	if (!iter)
		return -ENOMEM;

	err = seq_open(file, &bpffs_map_seq_ops);
	if (err) {
		map_iter_free(iter);
		return err;
	}

	m = file->private_data;
	m->private = iter;

	return 0;
}