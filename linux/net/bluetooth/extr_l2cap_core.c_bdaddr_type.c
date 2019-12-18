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
 scalar_t__ BDADDR_BREDR ; 
 scalar_t__ BDADDR_LE_PUBLIC ; 
 scalar_t__ BDADDR_LE_RANDOM ; 
 scalar_t__ LE_LINK ; 

__attribute__((used)) static inline u8 bdaddr_type(u8 link_type, u8 bdaddr_type)
{
	if (link_type == LE_LINK) {
		if (bdaddr_type == ADDR_LE_DEV_PUBLIC)
			return BDADDR_LE_PUBLIC;
		else
			return BDADDR_LE_RANDOM;
	}

	return BDADDR_BREDR;
}