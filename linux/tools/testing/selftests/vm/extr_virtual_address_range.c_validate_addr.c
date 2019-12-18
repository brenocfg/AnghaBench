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
 unsigned long HIGH_ADDR_MARK ; 
 int /*<<< orphan*/  printf (char*,unsigned long) ; 

__attribute__((used)) static int validate_addr(char *ptr, int high_addr)
{
	unsigned long addr = (unsigned long) ptr;

	if (high_addr) {
		if (addr < HIGH_ADDR_MARK) {
			printf("Bad address %lx\n", addr);
			return 1;
		}
		return 0;
	}

	if (addr > HIGH_ADDR_MARK) {
		printf("Bad address %lx\n", addr);
		return 1;
	}
	return 0;
}