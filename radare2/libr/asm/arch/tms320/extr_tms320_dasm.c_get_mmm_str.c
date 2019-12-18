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

/* Variables and functions */

const char * get_mmm_str(ut8 key, char * str)
{
	switch (key & 7) {
	default:
	case 0x00: return "*ARn";
	case 0x01: return "*ARn+";
	case 0x02: return "*ARn-";
		// TODO:
		//	C54CM:0 => *(ARn + T0)
		//	C54CM:1 => *(ARn + AR0)
	case 0x03: return "*(ARn + t0)";
	case 0x04: return "*(ARn + t1)";
		// TODO:
		//	C54CM:0 => *(ARn - t0)
		//	C54CM:1 => *(ARn - AR0)
	case 0x05: return "*(ARn - t0)";
	case 0x06: return "*(ARn - t1)";
		// TODO:
		//	C54CM:0 => *ARn(T0)
		//	C54CM:1 => *ARn(AR0)
	case 0x07: return "*ARn(t0)";
	};
}