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
typedef  unsigned int u32 ;

/* Variables and functions */
 scalar_t__ arch_get_random_int (unsigned int*) ; 
 scalar_t__ arch_get_random_seed_int (unsigned int*) ; 

__attribute__((used)) static u32 __extract_hwseed(void)
{
	unsigned int val = 0;

	(void)(arch_get_random_seed_int(&val) ||
	       arch_get_random_int(&val));

	return val;
}