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
 scalar_t__ const AR9170_SRAM_OFFSET ; 
 scalar_t__ const AR9170_SRAM_SIZE ; 

__attribute__((used)) static bool valid_dma_addr(const u32 address)
{
	if (address >= AR9170_SRAM_OFFSET &&
	    address < (AR9170_SRAM_OFFSET + AR9170_SRAM_SIZE))
		return true;

	return false;
}