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
typedef  unsigned long uint16_t ;

/* Variables and functions */
 scalar_t__ add_csum_hword (unsigned long const*,int) ; 

__attribute__((used)) static uint16_t build_ip_csum(const uint16_t *start, int num_u16,
			      unsigned long sum)
{
	sum += add_csum_hword(start, num_u16);

	while (sum >> 16)
		sum = (sum & 0xffff) + (sum >> 16);

	return ~sum;
}