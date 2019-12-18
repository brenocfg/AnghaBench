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
 scalar_t__ r_str_startswith (char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static ut8 interpret_msrbank (char *str, ut8 *spsr) {
	const char fields[] = {'c', 'x', 's', 'f', 0};
	int res = 0;
	int i, j;
	if (r_str_startswith (str, "spsr_")) {
		*spsr = 1;
	} else {
		*spsr = 0;
	}		
	
	if (r_str_startswith (str, "apsr_")) {
		if (!(strcmp (str+5, "g"))) {
			return 0x4;
		}
		if (!(strcmp (str+5, "nzcvq"))) {
			return 0x8;
		}
		if (!(strcmp (str+5, "nzcvqg"))) {
			return 0xc;
		}
	}
	if (r_str_startswith (str, "cpsr_") || r_str_startswith (str, "spsr_")) {
		for (i = 0; str[5+i]; i++) {
			for (j = 0; fields[j]; j++) {
				if (str[5+i] == fields[j]) {
					break;
				}
			}
			if (!(fields[j])) {
				return 0;
			}
			res |= 1 << j;
		}
		return res;
	}
	return 0;
}