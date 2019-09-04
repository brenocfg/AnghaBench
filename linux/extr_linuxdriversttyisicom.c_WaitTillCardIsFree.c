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
 int inw (unsigned long) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static int WaitTillCardIsFree(unsigned long base)
{
	unsigned int count = 0;

	while (!(inw(base + 0xe) & 0x1) && count++ < 100)
		mdelay(1);

	return !(inw(base + 0xe) & 0x1);
}