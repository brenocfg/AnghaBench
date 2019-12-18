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
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

const char * get_smem_str(ut8 key, char * str)
{
	// direct memory

	if ((key & 0x01) == 0) {
#ifdef IDA_COMPATIBLE_MODE
		sprintf(str, "*sp(#%Xh)", key >> 1);
#else
		sprintf(str, "@0x%02X", key >> 1);
#endif
		return str;
	}

	// indirect memory

	switch (key) {
	case 0x11: return "abs16(k16)";
	case 0x31: return "*(k23)";
	case 0x51: return "port(k16)";
	case 0x71: return "*cdp";
	case 0x91: return "*cdp+";
	case 0xB1: return "*cdp-";
	case 0xD1: return "*cdp(K16)";
	case 0xF1: return "*+cdp(K16)";
	}

	switch (key & 0x1F) {
	case 0x01: return "*ARn";
	case 0x03: return "*ARn+";
	case 0x05: return "*ARn-";
		// TODO:
		//	C54CM:0 => *(ARn + T0)
		//	C54CM:1 => *(ARn + AR0)
	case 0x07: return "*(ARn + t0)";
		// TODO:
		//	C54CM:0 => *(ARn - t0)
		//	C54CM:1 => *(ARn - AR0)
	case 0x09: return "*(ARn - t0)";
		// TODO:
		//	C54CM:0 => *ARn(t0)
		//	C54CM:1 => *ARn(AR0)
	case 0x0B: return "*ARn(t0)";
	case 0x0D: return "*ARn(k16)";
	case 0x0F: return "*+ARn(k16)";
		// TODO:
		//	ARMS:0 => *(ARn + T1)
		//	ARMS:1 => *ARn(short(1))
	case 0x13: return "*(ARn + t1)";
		// TODO:
		//	ARMS:0 => *(ARn - T1)
		//	ARMS:1 => *ARn(short(2))
	case 0x15: return "*(ARn - t1)";
		// TODO:
		//	ARMS:0 => *ARn(T1)
		//	ARMS:1 => *ARn(short(3))
	case 0x17: return "*ARn(t1)";
		// TODO:
		//	ARMS:0 => *+ARn
		//	ARMS:1 => *ARn(short(4))
	case 0x19: return "*+ARn";
		// TODO:
		//	ARMS:0 => *-ARn
		//	ARMS:1 => *ARn(short(5))
	case 0x1B: return "*-ARn";
		// TODO:
		//	ARMS:0 => *(ARn + t0b)
		//	ARMS:1 => *ARn(short(6))
	case 0x1D: return "*(ARn + t0b)";
		// TODO:
		//	ARMS:0 => *(arn - t0b)
		//	ARMS:1 => *arn(short(7))
	case 0x1F: return "*(ARn - t0b)";
	}

	return "invalid";
}