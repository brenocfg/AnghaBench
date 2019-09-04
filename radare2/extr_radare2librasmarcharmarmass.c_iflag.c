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
typedef  size_t ut8 ;
typedef  int st8 ;

/* Variables and functions */
 int /*<<< orphan*/  r_str_case (char*,int) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static st8 iflag(char *input) {
	st8 res = 0;
	ut8 i;
	r_str_case (input, false);
	
	for (i = 0; i < strlen(input); i++) {
		switch (input[i]) {
		case 'a':
			res |= 0x4;
			break;
		case 'i':
			res |= 0x2;
			break;
		case 'f':
			res |= 0x1;
			break;
		default:
			return -1;
		}
	}
	return res;
}