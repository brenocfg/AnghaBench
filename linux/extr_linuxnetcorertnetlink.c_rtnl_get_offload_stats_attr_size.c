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
struct rtnl_link_stats64 {int dummy; } ;

/* Variables and functions */
#define  IFLA_OFFLOAD_XSTATS_CPU_HIT 128 

__attribute__((used)) static int rtnl_get_offload_stats_attr_size(int attr_id)
{
	switch (attr_id) {
	case IFLA_OFFLOAD_XSTATS_CPU_HIT:
		return sizeof(struct rtnl_link_stats64);
	}

	return 0;
}