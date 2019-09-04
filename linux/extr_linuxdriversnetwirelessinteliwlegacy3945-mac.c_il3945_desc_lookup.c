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

__attribute__((used)) static const char *
il3945_desc_lookup(int i)
{
	switch (i) {
	case 1:
		return "FAIL";
	case 2:
		return "BAD_PARAM";
	case 3:
		return "BAD_CHECKSUM";
	case 4:
		return "NMI_INTERRUPT";
	case 5:
		return "SYSASSERT";
	case 6:
		return "FATAL_ERROR";
	}

	return "UNKNOWN";
}