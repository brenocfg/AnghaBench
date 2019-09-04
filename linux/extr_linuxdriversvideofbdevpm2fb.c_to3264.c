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

__attribute__((used)) static u32 to3264(u32 timing, int bpp, int is64)
{
	switch (bpp) {
	case 24:
		timing *= 3;
		/* fall through */
	case 8:
		timing >>= 1;
		/* fall through */
	case 16:
		timing >>= 1;
	case 32:
		break;
	}
	if (is64)
		timing >>= 1;
	return timing;
}