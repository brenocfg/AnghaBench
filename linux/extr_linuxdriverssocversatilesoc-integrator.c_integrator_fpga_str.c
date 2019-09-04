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
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static const char *integrator_fpga_str(u32 id)
{
	switch ((id >> 12) & 0xf) {
	case 0x01:
		return "XC4062";
	case 0x02:
		return "XC4085";
	case 0x03:
		return "XVC600";
	case 0x04:
		return "EPM7256AE (Altera PLD)";
	default:
		return "Unknown";
	}
}