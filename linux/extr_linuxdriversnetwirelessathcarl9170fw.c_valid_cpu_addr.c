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

/* Variables and functions */
 scalar_t__ const AR9170_PRAM_OFFSET ; 
 scalar_t__ const AR9170_PRAM_SIZE ; 
 scalar_t__ valid_dma_addr (scalar_t__ const) ; 

__attribute__((used)) static bool valid_cpu_addr(const u32 address)
{
	if (valid_dma_addr(address) || (address >= AR9170_PRAM_OFFSET &&
	    address < (AR9170_PRAM_OFFSET + AR9170_PRAM_SIZE)))
		return true;

	return false;
}