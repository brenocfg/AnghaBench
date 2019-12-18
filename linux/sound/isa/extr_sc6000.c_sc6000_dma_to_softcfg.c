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

__attribute__((used)) static unsigned char sc6000_dma_to_softcfg(int dma)
{
	unsigned char val = 0;

	switch (dma) {
	case 0:
		val = 1;
		break;
	case 1:
		val = 2;
		break;
	case 3:
		val = 3;
		break;
	default:
		break;
	}
	return val;
}