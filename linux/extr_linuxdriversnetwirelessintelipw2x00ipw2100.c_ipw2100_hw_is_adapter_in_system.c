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
typedef  scalar_t__ u32 ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IPW_DATA_DOA_DEBUG_VALUE ; 
 int /*<<< orphan*/  IPW_REG_DOA_DEBUG_AREA_START ; 
 int /*<<< orphan*/  read_register (struct net_device*,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static bool ipw2100_hw_is_adapter_in_system(struct net_device *dev)
{
	u32 dbg;

	read_register(dev, IPW_REG_DOA_DEBUG_AREA_START, &dbg);

	return dbg == IPW_DATA_DOA_DEBUG_VALUE;
}