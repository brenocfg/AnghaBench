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
 char* get_freg_str (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

const char * get_cond_str(ut8 key, char * str)
{
	/* 000 FSSS ... 101 FSSS */
	if ((key >> 4) <= 5) {
		static const char * op[6] = { "==", "!=", "<", "<=", ">", ">=" };
		sprintf(str, "%s %s 0", get_freg_str(key & 15, NULL), op[(key >> 4) & 7]);
		return str;
	}

	/* 110 00SS */
	if ((key >> 2) == 0x18) {
		sprintf(str, "overflow(ac%d)", key & 3);
		return str;
	}

	/* 111 00SS */
	if ((key >> 2) == 0x1C) {
		sprintf(str, "!overflow(ac%d)", key & 3);
		return str;
	}

	switch (key) {
	case 0x64: return "tc1";
	case 0x65: return "tc2";
	case 0x66: return "carry";
	case 0x74: return "!tc1";
	case 0x75: return "!tc2";
	case 0x76: return "!carry";
		/* "&" operation */
	case 0x68: return "tc1 & tc2";
	case 0x69: return "tc1 & !tc2";
	case 0x6A: return "!tc1 & tc2";
	case 0x6B: return "!tc1 & !tc2";
		/* "|" operation */
	case 0x78: return "tc1 | tc2";
	case 0x79: return "tc1 | !tc2";
	case 0x7A: return "!tc1 | tc2";
	case 0x7B: return "!tc1 | !tc2";
		/* "^" operation */
	case 0x7C: return "tc1 ^ tc2";
	case 0x7D: return "tc1 ^ !tc2";
	case 0x7E: return "!tc1 ^ tc2";
	case 0x7F: return "!tc1 ^ !tc2";
	}

	return "invalid";
}