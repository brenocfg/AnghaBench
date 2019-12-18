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
struct netns_ipvs {int /*<<< orphan*/  dest_trash_lock; int /*<<< orphan*/  dest_trash; int /*<<< orphan*/  dest_trash_timer; } ;
struct ip_vs_dest {scalar_t__ idle_start; int /*<<< orphan*/  t_list; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  port; int /*<<< orphan*/  addr; int /*<<< orphan*/  af; int /*<<< orphan*/  stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP_VS_DBG_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IP_VS_DBG_BUF (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IP_VS_DEST_TRASH_PERIOD ; 
 int /*<<< orphan*/  ip_vs_rs_unhash (struct ip_vs_dest*) ; 
 int /*<<< orphan*/  ip_vs_stop_estimator (struct netns_ipvs*,int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __ip_vs_del_dest(struct netns_ipvs *ipvs, struct ip_vs_dest *dest,
			     bool cleanup)
{
	ip_vs_stop_estimator(ipvs, &dest->stats);

	/*
	 *  Remove it from the d-linked list with the real services.
	 */
	ip_vs_rs_unhash(dest);

	spin_lock_bh(&ipvs->dest_trash_lock);
	IP_VS_DBG_BUF(3, "Moving dest %s:%u into trash, dest->refcnt=%d\n",
		      IP_VS_DBG_ADDR(dest->af, &dest->addr), ntohs(dest->port),
		      refcount_read(&dest->refcnt));
	if (list_empty(&ipvs->dest_trash) && !cleanup)
		mod_timer(&ipvs->dest_trash_timer,
			  jiffies + (IP_VS_DEST_TRASH_PERIOD >> 1));
	/* dest lives in trash with reference */
	list_add(&dest->t_list, &ipvs->dest_trash);
	dest->idle_start = 0;
	spin_unlock_bh(&ipvs->dest_trash_lock);
}