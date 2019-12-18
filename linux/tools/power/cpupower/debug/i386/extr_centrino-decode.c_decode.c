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
 int /*<<< orphan*/  printf (char*,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static void decode (unsigned int msr)
{
	unsigned int multiplier;
	unsigned int mv;

	multiplier = ((msr >> 8) & 0xFF);

	mv = (((msr & 0xFF) * 16) + 700);

	printf("0x%x means multiplier %d @ %d mV\n", msr, multiplier, mv);
}