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
struct wa_rpipe {int /*<<< orphan*/  list_node; int /*<<< orphan*/  seg_list; int /*<<< orphan*/  seg_lock; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rpipe_init(struct wa_rpipe *rpipe)
{
	kref_init(&rpipe->refcnt);
	spin_lock_init(&rpipe->seg_lock);
	INIT_LIST_HEAD(&rpipe->seg_list);
	INIT_LIST_HEAD(&rpipe->list_node);
}