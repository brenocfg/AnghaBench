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
typedef  int u32 ;
struct hlist_head {int dummy; } ;
struct datapath {struct hlist_head* meters; } ;

/* Variables and functions */
 int METER_HASH_BUCKETS ; 

__attribute__((used)) static struct hlist_head *meter_hash_bucket(const struct datapath *dp,
					    u32 meter_id)
{
	return &dp->meters[meter_id & (METER_HASH_BUCKETS - 1)];
}