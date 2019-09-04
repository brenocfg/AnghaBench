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
 scalar_t__ ADDR_LE_DEV_PUBLIC ; 
 scalar_t__ ADDR_LE_DEV_RANDOM ; 
 scalar_t__ BDADDR_LE_PUBLIC ; 

__attribute__((used)) static u8 le_addr_type(u8 mgmt_addr_type)
{
	if (mgmt_addr_type == BDADDR_LE_PUBLIC)
		return ADDR_LE_DEV_PUBLIC;
	else
		return ADDR_LE_DEV_RANDOM;
}