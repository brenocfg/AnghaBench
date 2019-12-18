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

/* Variables and functions */
 int TIPC_ZONE_CLUSTER_MASK ; 

__attribute__((used)) static inline u32 tipc_cluster_mask(u32 addr)
{
	return addr & TIPC_ZONE_CLUSTER_MASK;
}