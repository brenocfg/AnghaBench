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

/* Variables and functions */
 int /*<<< orphan*/  r_str_case (char*,int) ; 
 scalar_t__ r_str_startswith (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static ut32 itmask(char *input) {
	ut32 res = 0;
	ut32 i, length;
	r_str_case (input, false);
	if (2 > strlen (input)) {
		return 0;
	}
	if (r_str_startswith (input, "it")) {
		input += 2;
		res |= 1; // matched
		if (strlen(input) > 3) {
			return 0;
		}
		res |= (strlen (input) & 0x3) << 4;
		length = strlen (input);
		for (i = 0; i < length; i++, input++ ) {
			if (*input == 'e') {
				res |= 1 << (3 - i);
				continue;
			}
			if (*input == 't') {
				continue;
			}
			return 0;
		}
		return res;
	}
	return 0;
}