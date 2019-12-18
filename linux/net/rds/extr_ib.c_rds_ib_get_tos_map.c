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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */

__attribute__((used)) static u8 rds_ib_get_tos_map(u8 tos)
{
	/* 1:1 user to transport map for RDMA transport.
	 * In future, if custom map is desired, hook can export
	 * user configurable map.
	 */
	return tos;
}