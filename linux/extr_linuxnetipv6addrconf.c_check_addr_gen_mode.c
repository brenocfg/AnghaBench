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
 int EINVAL ; 
 int IN6_ADDR_GEN_MODE_EUI64 ; 
 int IN6_ADDR_GEN_MODE_NONE ; 
 int IN6_ADDR_GEN_MODE_RANDOM ; 
 int IN6_ADDR_GEN_MODE_STABLE_PRIVACY ; 

__attribute__((used)) static int check_addr_gen_mode(int mode)
{
	if (mode != IN6_ADDR_GEN_MODE_EUI64 &&
	    mode != IN6_ADDR_GEN_MODE_NONE &&
	    mode != IN6_ADDR_GEN_MODE_STABLE_PRIVACY &&
	    mode != IN6_ADDR_GEN_MODE_RANDOM)
		return -EINVAL;
	return 1;
}