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

__attribute__((used)) static char *trace_decode_reg(int reg)
{
	switch (reg) {
		case 769: return "SPRN_MMCR2"; break;
		case 770: return "SPRN_MMCRA"; break;
		case 779: return "SPRN_MMCR0"; break;
		case 804: return "SPRN_EBBHR"; break;
		case 805: return "SPRN_EBBRR"; break;
		case 806: return "SPRN_BESCR"; break;
		case 800: return "SPRN_BESCRS"; break;
		case 801: return "SPRN_BESCRSU"; break;
		case 802: return "SPRN_BESCRR"; break;
		case 803: return "SPRN_BESCRRU"; break;
		case 771: return "SPRN_PMC1"; break;
		case 772: return "SPRN_PMC2"; break;
		case 773: return "SPRN_PMC3"; break;
		case 774: return "SPRN_PMC4"; break;
		case 775: return "SPRN_PMC5"; break;
		case 776: return "SPRN_PMC6"; break;
		case 780: return "SPRN_SIAR"; break;
		case 781: return "SPRN_SDAR"; break;
		case 768: return "SPRN_SIER"; break;
	}

	return NULL;
}