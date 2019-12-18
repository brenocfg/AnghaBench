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
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ ipv4_is_lbcast (int /*<<< orphan*/ ) ; 
 scalar_t__ ipv4_is_multicast (int /*<<< orphan*/ ) ; 
 scalar_t__ ipv4_is_zeronet (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __be32 get_saddr(__be32 addr)
{
	if (ipv4_is_multicast(addr) || ipv4_is_lbcast(addr) ||
	    ipv4_is_zeronet(addr))
		return 0;
	return addr;
}