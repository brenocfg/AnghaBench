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
typedef  int ut16 ;

/* Variables and functions */

__attribute__((used)) static bool parse_hexadecimal(char const* hexstr, ut16* out) {
	if ( !hexstr || hexstr[0] != '0'
		|| !(hexstr[1] == 'x' || hexstr[1] == 'X')) {
		return false;
	}
	*out = 0;
	char const*p;
	for (p = hexstr + 2; p < hexstr + 6 && *p ; p += 1) {
		*out <<= 4;
		if ( '0' <= *p && *p <= '9' ) {
			*out |= *p - '0';
		} else if ( 'a' <= *p && *p <= 'f' ) {
			*out |= *p - 'a' + 10;
		} else if ( 'A' <= *p && *p <= 'F' ) {
			*out |= *p - 'A' + 10;
		} else {
			return false;
		}
	}
	return ! *p;
}