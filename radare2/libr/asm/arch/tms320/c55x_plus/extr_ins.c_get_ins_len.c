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
typedef  int ut8 ;
typedef  int ut32 ;

/* Variables and functions */

ut32 get_ins_len(ut8 opcode) {
	ut32 val = (opcode >> 4) & 0xF;
	ut32 len = 0;

	switch (val) {
	case 0:
	case 1:
		len = 2;
		break;
	case 2:
	case 3:
		len = 1;
		break;
	case 4:
	case 5:
	case 6:
	case 7:
		len = 3;
		break;
	case 8:
	case 9:
	case 10:
		len = 4;
		break;
	case 11:
	case 12:
	case 13:
		len = 5;
		break;
	case 14:
		len = 6;
		break;
	case 15:
		len = 7;
		break;
	}

	return len;
}