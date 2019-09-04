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
typedef  int u8 ;

/* Variables and functions */

__attribute__((used)) static u8 dma_speed_hw(int dma_speed)
{
	switch (dma_speed) {
	case 5:
		return 0x00;
	case 6:
		return 0x04;
	case 7:
		return 0x01;
	case 8:
		return 0x02;
	case 10:
		return 0x03;
	}

	return 0xff;	/* invalid */
}