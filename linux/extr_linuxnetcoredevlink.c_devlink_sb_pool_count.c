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
typedef  scalar_t__ u16 ;
struct devlink_sb {scalar_t__ egress_pools_count; scalar_t__ ingress_pools_count; } ;

/* Variables and functions */

__attribute__((used)) static u16 devlink_sb_pool_count(struct devlink_sb *devlink_sb)
{
	return devlink_sb->ingress_pools_count + devlink_sb->egress_pools_count;
}