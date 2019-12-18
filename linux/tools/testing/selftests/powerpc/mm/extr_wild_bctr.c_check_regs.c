#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__* gpr; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL_IF (int) ; 
 scalar_t__ POISONED_REG (unsigned long) ; 
 int /*<<< orphan*/  printf (char*) ; 
 TYPE_1__ signal_regs ; 

__attribute__((used)) static int check_regs(void)
{
	unsigned long i;

	for (i = 15; i <= 29; i++)
		FAIL_IF(signal_regs.gpr[i] != POISONED_REG(i));

	printf("Regs OK\n");
	return 0;
}