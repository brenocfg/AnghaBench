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
typedef  scalar_t__ uint8_t ;
typedef  int uint16_t ;
struct ipv6hdr {int dummy; } ;

/* Variables and functions */
 int htons (int) ; 
 int ntohs (int) ; 

__attribute__((used)) static void ipv6_set_dsfield(struct ipv6hdr *ip6h, uint8_t dsfield)
{
	uint16_t val, *ptr = (uint16_t *)ip6h;

	val = ntohs(*ptr);
	val &= 0xF00F;
	val |= ((uint16_t) dsfield) << 4;
	*ptr = htons(val);
}