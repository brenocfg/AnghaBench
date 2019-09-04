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

/* Variables and functions */
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  o2hb_callback_sem ; 
 int /*<<< orphan*/  o2hb_fill_node_map_from_callback (unsigned long*,unsigned int) ; 
 int /*<<< orphan*/  o2hb_live_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

void o2hb_fill_node_map(unsigned long *map, unsigned bytes)
{
	/* callers want to serialize this map and callbacks so that they
	 * can trust that they don't miss nodes coming to the party */
	down_read(&o2hb_callback_sem);
	spin_lock(&o2hb_live_lock);
	o2hb_fill_node_map_from_callback(map, bytes);
	spin_unlock(&o2hb_live_lock);
	up_read(&o2hb_callback_sem);
}