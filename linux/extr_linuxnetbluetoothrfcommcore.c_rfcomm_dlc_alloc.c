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
struct rfcomm_dlc {int /*<<< orphan*/  refcnt; int /*<<< orphan*/  lock; int /*<<< orphan*/  tx_queue; int /*<<< orphan*/  timer; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct rfcomm_dlc*) ; 
 struct rfcomm_dlc* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rfcomm_dlc_clear_state (struct rfcomm_dlc*) ; 
 int /*<<< orphan*/  rfcomm_dlc_timeout ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct rfcomm_dlc *rfcomm_dlc_alloc(gfp_t prio)
{
	struct rfcomm_dlc *d = kzalloc(sizeof(*d), prio);

	if (!d)
		return NULL;

	timer_setup(&d->timer, rfcomm_dlc_timeout, 0);

	skb_queue_head_init(&d->tx_queue);
	mutex_init(&d->lock);
	refcount_set(&d->refcnt, 1);

	rfcomm_dlc_clear_state(d);

	BT_DBG("%p", d);

	return d;
}