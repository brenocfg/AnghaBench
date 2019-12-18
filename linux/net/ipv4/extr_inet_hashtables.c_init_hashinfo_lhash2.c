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
struct inet_hashinfo {int lhash2_mask; TYPE_1__* lhash2; } ;
struct TYPE_2__ {scalar_t__ count; int /*<<< orphan*/  head; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void init_hashinfo_lhash2(struct inet_hashinfo *h)
{
	int i;

	for (i = 0; i <= h->lhash2_mask; i++) {
		spin_lock_init(&h->lhash2[i].lock);
		INIT_HLIST_HEAD(&h->lhash2[i].head);
		h->lhash2[i].count = 0;
	}
}