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

st32 get_hashfunc_28(st32 arg1, st32 arg2) {
	st32 v2; 
	st32 v3; 
	char v5; 

	v2 = arg2;
	v3 = v2 & 0x1F800;
	if ( (ut32)v3 <= 0xA000 ) {
		if ( v3 != 40960 ) {
			if ( (ut32)v3 <= 0x3000 ) {
				if (v3 == 12288) {
					return 384;
				}
				if ( (ut32)v3 <= 0x1800 ) {
					if ( v3 != 6144 && v3 && v3 != 2048 ) {
						if (v3 == 4096) {
							return 384;
						}
						return arg1;
					}
					return 384;
				}
				if (v3 == 8192 || v3 == 10240) {
					return 384;
				}
				return arg1;
			}
			if ( (ut32)v3 > 0x8800 ) {
				if ( v3 != 36864 ) {
					if (v3 == 38912) {
						return 385;
					}
					return arg1;
				}
			} else {
				if ( v3 != 34816 ) {
					if ( v3 != 14336 ) {
						if (v3 == 24576) {
							return 388;
						}
						if (v3 == 32768) {
							return 385;
						}
						return arg1;
					}
					return 384;
				}
			}
		}
		return 385;
	}
	if ( (ut32)v3 <= 0x11000 ) {
		if (v3 == 69632) {
			return 386;
		}
		if ( (ut32)v3 <= 0xE000 ) {
			if (v3 == 57344) {
				return 387;
			}
			if (v3 != 43008 && v3 != 45056 && v3 != 47104) {
				return arg1;
			}
			return 385;
		}
		if (v3 == 65536) {
			return 386;
		}
		v5 = v3 == 67584;
		LABEL_35:
			if (!v5) {
				return arg1;
			}
			return 386;
	}
	if ( (ut32)v3 <= 0x13000 ) {
		if (v3 == 77824 || v3 == 71680 || v3 == 73728) {
			return 386;
		}
		v5 = v3 == 75776;
		goto LABEL_35;
	}
	if (v3 == 79872) {
		return 386;
	}
	if (v3 != 90112) {
		return arg1;
	}
	return 389;
}