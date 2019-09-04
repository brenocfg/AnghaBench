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
struct net_device {int /*<<< orphan*/  napi_list; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  function; } ;
struct napi_struct {int (* poll ) (struct napi_struct*,int) ;int weight; int /*<<< orphan*/  state; struct net_device* dev; int /*<<< orphan*/  dev_list; int /*<<< orphan*/ * skb; TYPE_1__ timer; int /*<<< orphan*/  poll_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL_PINNED ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int NAPI_POLL_WEIGHT ; 
 int /*<<< orphan*/  NAPI_STATE_SCHED ; 
 int /*<<< orphan*/  hrtimer_init (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_gro_hash (struct napi_struct*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_hash_add (struct napi_struct*) ; 
 int /*<<< orphan*/  napi_watchdog ; 
 int /*<<< orphan*/  pr_err_once (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void netif_napi_add(struct net_device *dev, struct napi_struct *napi,
		    int (*poll)(struct napi_struct *, int), int weight)
{
	INIT_LIST_HEAD(&napi->poll_list);
	hrtimer_init(&napi->timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL_PINNED);
	napi->timer.function = napi_watchdog;
	init_gro_hash(napi);
	napi->skb = NULL;
	napi->poll = poll;
	if (weight > NAPI_POLL_WEIGHT)
		pr_err_once("netif_napi_add() called with weight %d on device %s\n",
			    weight, dev->name);
	napi->weight = weight;
	list_add(&napi->dev_list, &dev->napi_list);
	napi->dev = dev;
#ifdef CONFIG_NETPOLL
	napi->poll_owner = -1;
#endif
	set_bit(NAPI_STATE_SCHED, &napi->state);
	napi_hash_add(napi);
}