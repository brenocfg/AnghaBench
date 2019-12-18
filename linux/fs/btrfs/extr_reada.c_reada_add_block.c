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
typedef  int /*<<< orphan*/  u64 ;
struct reada_extent {int /*<<< orphan*/  lock; int /*<<< orphan*/  extctl; } ;
struct reada_extctl {int /*<<< orphan*/  list; int /*<<< orphan*/  generation; struct reada_control* rc; } ;
struct reada_control {int /*<<< orphan*/  elems; struct btrfs_fs_info* fs_info; } ;
struct btrfs_key {int dummy; } ;
struct btrfs_fs_info {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct reada_extctl* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reada_extent_put (struct btrfs_fs_info*,struct reada_extent*) ; 
 struct reada_extent* reada_find_extent (struct btrfs_fs_info*,int /*<<< orphan*/ ,struct btrfs_key*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int reada_add_block(struct reada_control *rc, u64 logical,
			   struct btrfs_key *top, u64 generation)
{
	struct btrfs_fs_info *fs_info = rc->fs_info;
	struct reada_extent *re;
	struct reada_extctl *rec;

	/* takes one ref */
	re = reada_find_extent(fs_info, logical, top);
	if (!re)
		return -1;

	rec = kzalloc(sizeof(*rec), GFP_KERNEL);
	if (!rec) {
		reada_extent_put(fs_info, re);
		return -ENOMEM;
	}

	rec->rc = rc;
	rec->generation = generation;
	atomic_inc(&rc->elems);

	spin_lock(&re->lock);
	list_add_tail(&rec->list, &re->extctl);
	spin_unlock(&re->lock);

	/* leave the ref on the extent */

	return 0;
}