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

__attribute__((used)) static const char *integrator_arch_str(u32 id)
{
	switch ((id >> 16) & 0xff) {
	case 0x00:
		return "ASB little-endian";
	case 0x01:
		return "AHB little-endian";
	case 0x03:
		return "AHB-Lite system bus, bi-endian";
	case 0x04:
		return "AHB";
	case 0x08:
		return "AHB system bus, ASB processor bus";
	default:
		return "Unknown";
	}
}