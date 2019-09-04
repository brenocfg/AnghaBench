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

/* Variables and functions */
 int ether_addr_equal_unaligned (void const*,void const*) ; 

__attribute__((used)) static inline bool batadv_compare_eth(const void *data1, const void *data2)
{
	return ether_addr_equal_unaligned(data1, data2);
}