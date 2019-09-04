#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ax25_node; } ;
typedef  TYPE_1__ ax25_cb ;

/* Variables and functions */
 int /*<<< orphan*/  ax25_cb_put (TYPE_1__*) ; 
 int /*<<< orphan*/  ax25_list_lock ; 
 int /*<<< orphan*/  hlist_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_unhashed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ax25_cb_del(ax25_cb *ax25)
{
	if (!hlist_unhashed(&ax25->ax25_node)) {
		spin_lock_bh(&ax25_list_lock);
		hlist_del_init(&ax25->ax25_node);
		spin_unlock_bh(&ax25_list_lock);
		ax25_cb_put(ax25);
	}
}