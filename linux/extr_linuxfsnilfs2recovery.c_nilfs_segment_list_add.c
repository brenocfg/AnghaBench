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
struct nilfs_segment_entry {int /*<<< orphan*/  list; int /*<<< orphan*/  segnum; } ;
struct list_head {int dummy; } ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct nilfs_segment_entry* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int nilfs_segment_list_add(struct list_head *head, __u64 segnum)
{
	struct nilfs_segment_entry *ent = kmalloc(sizeof(*ent), GFP_NOFS);

	if (unlikely(!ent))
		return -ENOMEM;

	ent->segnum = segnum;
	INIT_LIST_HEAD(&ent->list);
	list_add_tail(&ent->list, head);
	return 0;
}