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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ CLUSTER_IDS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  clear_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wusb_cluster_id_table ; 
 int /*<<< orphan*/  wusb_cluster_ids_lock ; 

void wusb_cluster_id_put(u8 id)
{
	id = 0xff - id;
	BUG_ON(id >= CLUSTER_IDS);
	spin_lock(&wusb_cluster_ids_lock);
	WARN_ON(!test_bit(id, wusb_cluster_id_table));
	clear_bit(id, wusb_cluster_id_table);
	spin_unlock(&wusb_cluster_ids_lock);
}