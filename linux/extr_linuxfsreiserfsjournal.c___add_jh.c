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
struct reiserfs_journal {int /*<<< orphan*/  j_dirty_buffers_lock; TYPE_1__* j_current_jl; } ;
struct reiserfs_jh {TYPE_1__* jl; int /*<<< orphan*/  list; struct buffer_head* bh; } ;
struct buffer_head {struct reiserfs_jh* b_private; } ;
struct TYPE_2__ {int /*<<< orphan*/  j_bh_list; int /*<<< orphan*/  j_tail_bh_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (struct reiserfs_jh*) ; 
 struct reiserfs_jh* alloc_jh () ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int __add_jh(struct reiserfs_journal *j, struct buffer_head *bh,
			   int tail)
{
	struct reiserfs_jh *jh;

	if (bh->b_private) {
		spin_lock(&j->j_dirty_buffers_lock);
		if (!bh->b_private) {
			spin_unlock(&j->j_dirty_buffers_lock);
			goto no_jh;
		}
		jh = bh->b_private;
		list_del_init(&jh->list);
	} else {
no_jh:
		get_bh(bh);
		jh = alloc_jh();
		spin_lock(&j->j_dirty_buffers_lock);
		/*
		 * buffer must be locked for __add_jh, should be able to have
		 * two adds at the same time
		 */
		BUG_ON(bh->b_private);
		jh->bh = bh;
		bh->b_private = jh;
	}
	jh->jl = j->j_current_jl;
	if (tail)
		list_add_tail(&jh->list, &jh->jl->j_tail_bh_list);
	else {
		list_add_tail(&jh->list, &jh->jl->j_bh_list);
	}
	spin_unlock(&j->j_dirty_buffers_lock);
	return 0;
}