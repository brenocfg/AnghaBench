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
struct inet_hashinfo {int /*<<< orphan*/ * lhash2; TYPE_1__* listening_hash; } ;
struct TYPE_2__ {scalar_t__ count; int /*<<< orphan*/  head; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int INET_LHTABLE_SIZE ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void inet_hashinfo_init(struct inet_hashinfo *h)
{
	int i;

	for (i = 0; i < INET_LHTABLE_SIZE; i++) {
		spin_lock_init(&h->listening_hash[i].lock);
		INIT_HLIST_HEAD(&h->listening_hash[i].head);
		h->listening_hash[i].count = 0;
	}

	h->lhash2 = NULL;
}