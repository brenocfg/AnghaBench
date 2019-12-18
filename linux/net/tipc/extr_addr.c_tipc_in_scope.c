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
 int TIPC_ZONE_MASK ; 
 int tipc_cluster_mask (int) ; 

bool tipc_in_scope(bool legacy_format, u32 domain, u32 addr)
{
	if (!domain || (domain == addr))
		return true;
	if (!legacy_format)
		return false;
	if (domain == tipc_cluster_mask(addr)) /* domain <Z.C.0> */
		return true;
	if (domain == (addr & TIPC_ZONE_CLUSTER_MASK)) /* domain <Z.C.0> */
		return true;
	if (domain == (addr & TIPC_ZONE_MASK)) /* domain <Z.0.0> */
		return true;
	return false;
}