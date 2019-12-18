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
struct ax25_linkfail {int /*<<< orphan*/  lf_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  ax25_linkfail_list ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  linkfail_lock ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void ax25_linkfail_register(struct ax25_linkfail *lf)
{
	spin_lock_bh(&linkfail_lock);
	hlist_add_head(&lf->lf_node, &ax25_linkfail_list);
	spin_unlock_bh(&linkfail_lock);
}