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
typedef  int ut64 ;
typedef  int ut32 ;
typedef  int st32 ;

/* Variables and functions */
 int err ; 
 int firstsigdigit (int) ; 
 int getnum (char const*) ; 

__attribute__((used)) static ut32 getthimmed12(const char *str) {
	ut64 num = getnum (str);
	if (err) {
		return 0;
	}

	st32 FSD = 0;
	ut64 result = 0;
	if (num <= 0xff) {
		return num << 8;
	} else if ( ((num & 0xff00ff00) == 0) && ((num & 0x00ff0000) == ((num & 0x000000ff) << 16)) ) {
		result |= (num & 0x000000ff) << 8;
		result |= 0x00000010;
		return result;
	} else if ( ((num & 0x00ff00ff) == 0) && ((num & 0xff000000) == ((num & 0x0000ff00) << 16)) ) {
		result |= num & 0x0000ff00;
		result |= 0x00000020;
		return result;
	} else if ( ((num & 0xff000000) == ((num & 0x00ff0000) << 8)) && ((num & 0xff000000) == ((num & 0x0000ff00) << 16)) && ((num &0xff000000) == ((num & 0x000000ff) << 24)) ) {
		result |= num & 0x0000ff00;
		result |= 0x00000030;
		return result;
	} else {
		FSD = firstsigdigit(num);
		if (FSD != -1) {
		        result |= ((num >> (24-FSD)) & 0x0000007f) << 8;
			result |= ((8+FSD) & 0x1) << 15;
			result |= ((8+FSD) & 0xe) << 3;
			result |= ((8+FSD) & 0x10) << 14;
			return result;
		} else {
			err = true;
			return 0;
		}
	}
}