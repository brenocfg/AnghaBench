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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int MAX_ADDR_TESTED ; 
 int rand () ; 

uint8_t *get_random_addr()
{
	uint8_t*addr = (uint8_t *)(unsigned long)(rand() % MAX_ADDR_TESTED);
	return (addr - (unsigned long)addr % sizeof(uint8_t *));
}