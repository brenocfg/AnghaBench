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

__attribute__((used)) static unsigned char XG21GPIODataTransfer(unsigned char ujDate)
{
	unsigned char ujRet = 0;
	unsigned char i = 0;

	for (i = 0; i < 8; i++) {
		ujRet <<= 1;
		ujRet |= (ujDate >> i) & 1;
	}

	return ujRet;
}