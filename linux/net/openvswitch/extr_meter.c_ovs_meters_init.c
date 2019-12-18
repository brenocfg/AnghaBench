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
struct hlist_head {int dummy; } ;
struct datapath {int /*<<< orphan*/ * meters; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int METER_HASH_BUCKETS ; 
 int /*<<< orphan*/ * kmalloc_array (int,int,int /*<<< orphan*/ ) ; 

int ovs_meters_init(struct datapath *dp)
{
	int i;

	dp->meters = kmalloc_array(METER_HASH_BUCKETS,
				   sizeof(struct hlist_head), GFP_KERNEL);

	if (!dp->meters)
		return -ENOMEM;

	for (i = 0; i < METER_HASH_BUCKETS; i++)
		INIT_HLIST_HEAD(&dp->meters[i]);

	return 0;
}