#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {void* hard_packet_limit; void* hard_byte_limit; void* soft_packet_limit; void* soft_byte_limit; } ;
struct TYPE_6__ {int /*<<< orphan*/  add_time; } ;
struct TYPE_8__ {int /*<<< orphan*/  function; } ;
struct TYPE_5__ {int /*<<< orphan*/  all; } ;
struct xfrm_state {int /*<<< orphan*/  lock; scalar_t__ replay_maxdiff; scalar_t__ replay_maxage; TYPE_3__ lft; TYPE_2__ curlft; int /*<<< orphan*/  rtimer; TYPE_4__ mtimer; int /*<<< orphan*/  byspi; int /*<<< orphan*/  bysrc; int /*<<< orphan*/  bydst; TYPE_1__ km; int /*<<< orphan*/  tunnel_users; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  xs_net; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_BOOTTIME ; 
 int GFP_ATOMIC ; 
 int /*<<< orphan*/  HRTIMER_MODE_ABS_SOFT ; 
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 void* XFRM_INF ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_init (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct xfrm_state* kmem_cache_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ktime_get_real_seconds () ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_pnet (int /*<<< orphan*/ *,struct net*) ; 
 int /*<<< orphan*/  xfrm_replay_timer_handler ; 
 int /*<<< orphan*/  xfrm_state_cache ; 
 int /*<<< orphan*/  xfrm_timer_handler ; 

struct xfrm_state *xfrm_state_alloc(struct net *net)
{
	struct xfrm_state *x;

	x = kmem_cache_alloc(xfrm_state_cache, GFP_ATOMIC | __GFP_ZERO);

	if (x) {
		write_pnet(&x->xs_net, net);
		refcount_set(&x->refcnt, 1);
		atomic_set(&x->tunnel_users, 0);
		INIT_LIST_HEAD(&x->km.all);
		INIT_HLIST_NODE(&x->bydst);
		INIT_HLIST_NODE(&x->bysrc);
		INIT_HLIST_NODE(&x->byspi);
		hrtimer_init(&x->mtimer, CLOCK_BOOTTIME, HRTIMER_MODE_ABS_SOFT);
		x->mtimer.function = xfrm_timer_handler;
		timer_setup(&x->rtimer, xfrm_replay_timer_handler, 0);
		x->curlft.add_time = ktime_get_real_seconds();
		x->lft.soft_byte_limit = XFRM_INF;
		x->lft.soft_packet_limit = XFRM_INF;
		x->lft.hard_byte_limit = XFRM_INF;
		x->lft.hard_packet_limit = XFRM_INF;
		x->replay_maxage = 0;
		x->replay_maxdiff = 0;
		spin_lock_init(&x->lock);
	}
	return x;
}