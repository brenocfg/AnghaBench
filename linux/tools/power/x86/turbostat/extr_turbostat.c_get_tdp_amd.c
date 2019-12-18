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

double get_tdp_amd(unsigned int family)
{
	switch (family) {
	case 0x17:
	case 0x18:
	default:
		/* This is the max stock TDP of HEDT/Server Fam17h chips */
		return 250.0;
	}
}