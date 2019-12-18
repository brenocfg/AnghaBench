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
struct reiserfs_jh {int /*<<< orphan*/  list; int /*<<< orphan*/ * bh; } ;
struct buffer_head {struct reiserfs_jh* b_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct reiserfs_jh*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nr_reiserfs_jh ; 
 int /*<<< orphan*/  put_bh (struct buffer_head*) ; 

void reiserfs_free_jh(struct buffer_head *bh)
{
	struct reiserfs_jh *jh;

	jh = bh->b_private;
	if (jh) {
		bh->b_private = NULL;
		jh->bh = NULL;
		list_del_init(&jh->list);
		kfree(jh);
		if (atomic_read(&nr_reiserfs_jh) <= 0)
			BUG();
		atomic_dec(&nr_reiserfs_jh);
		put_bh(bh);
	}
}