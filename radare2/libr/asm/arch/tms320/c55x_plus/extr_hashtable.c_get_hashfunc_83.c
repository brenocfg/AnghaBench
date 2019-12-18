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
typedef  int ut32 ;
typedef  int st32 ;

/* Variables and functions */

st32 get_hashfunc_83(st32 arg1, st32 arg2) {
	st32 v2; 
	st32 result; 
	char v4; 

	v2 = arg2 & 0x1810180;
	if ( (arg2 & 0x1810180u) <= 0x800080 ) {
		if ( (arg2 & 0x1810180) != 8388736 ) {
			if ( (ut32)v2 <= 0x10000 ) {
				if (v2 == 65536) {
					return 193;
				}
				if ( (ut32)v2 <= 0x100 ) {
					if ( v2 != 256 ) {
						if ( v2 ) {
							if (v2 == 128) {
								return 197;
							}
							return arg1;
						}
						return 193;
					}
					return 202;
				}
				v4 = v2 == 384;
				LABEL_11:
					if (v4) {
						return 199;
					}
					return arg1;
			}
			if ( (ut32)v2 > 0x10180 ) {
				if (v2 == 8388608) {
					return 193;
				}
				return arg1;
			}
			if (v2 == 65920) {
				return 199;
			}
			if ( v2 != 65664 ) {
				if (v2 == 65792) {
					return 202;
				}
				return arg1;
			}
		}
		return 197;
	}
	if ( (ut32)v2 <= 0x810100 ) {
		if (v2 == 8454400) {
			return 202;
		}
		if ( (ut32)v2 <= 0x810000 ) {
			if (v2 == 8454144) {
				return 193;
			}
			if (v2 == 8388864) {
				return 202;
			}
			v4 = v2 == 8388992;
			goto LABEL_11;
		}
		if (v2 != 8454272) {
			return arg1;
		}
		return 197;
	}
	if (v2 == 8454528) {
		return 199;
	}
	if ( v2 == 16777216 ) {
		result = 205;
	} else {
		if (v2 != 16777344) {
			return arg1;
		}
		result = 206;
	}
	return result;
}