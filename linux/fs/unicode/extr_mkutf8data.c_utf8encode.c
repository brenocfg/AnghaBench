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

/* Variables and functions */
 char UTF8_2_BITS ; 
 char UTF8_3_BITS ; 
 char UTF8_4_BITS ; 
 char UTF8_N_BITS ; 
 unsigned int UTF8_V_MASK ; 
 unsigned int UTF8_V_SHIFT ; 
 int /*<<< orphan*/  printf (char*,unsigned int) ; 

__attribute__((used)) static int utf8encode(char *str, unsigned int val)
{
	int len;

	if (val < 0x80) {
		str[0] = val;
		len = 1;
	} else if (val < 0x800) {
		str[1] = val & UTF8_V_MASK;
		str[1] |= UTF8_N_BITS;
		val >>= UTF8_V_SHIFT;
		str[0] = val;
		str[0] |= UTF8_2_BITS;
		len = 2;
	} else if (val < 0x10000) {
		str[2] = val & UTF8_V_MASK;
		str[2] |= UTF8_N_BITS;
		val >>= UTF8_V_SHIFT;
		str[1] = val & UTF8_V_MASK;
		str[1] |= UTF8_N_BITS;
		val >>= UTF8_V_SHIFT;
		str[0] = val;
		str[0] |= UTF8_3_BITS;
		len = 3;
	} else if (val < 0x110000) {
		str[3] = val & UTF8_V_MASK;
		str[3] |= UTF8_N_BITS;
		val >>= UTF8_V_SHIFT;
		str[2] = val & UTF8_V_MASK;
		str[2] |= UTF8_N_BITS;
		val >>= UTF8_V_SHIFT;
		str[1] = val & UTF8_V_MASK;
		str[1] |= UTF8_N_BITS;
		val >>= UTF8_V_SHIFT;
		str[0] = val;
		str[0] |= UTF8_4_BITS;
		len = 4;
	} else {
		printf("%#x: illegal val\n", val);
		len = 0;
	}
	return len;
}