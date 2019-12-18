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
 unsigned char const UTF8_3_BITS ; 
 unsigned char const UTF8_4_BITS ; 
 unsigned int UTF8_V_SHIFT ; 

__attribute__((used)) static unsigned int utf8decode(const char *str)
{
	const unsigned char *s = (const unsigned char*)str;
	unsigned int unichar = 0;

	if (*s < 0x80) {
		unichar = *s;
	} else if (*s < UTF8_3_BITS) {
		unichar = *s++ & 0x1F;
		unichar <<= UTF8_V_SHIFT;
		unichar |= *s & 0x3F;
	} else if (*s < UTF8_4_BITS) {
		unichar = *s++ & 0x0F;
		unichar <<= UTF8_V_SHIFT;
		unichar |= *s++ & 0x3F;
		unichar <<= UTF8_V_SHIFT;
		unichar |= *s & 0x3F;
	} else {
		unichar = *s++ & 0x0F;
		unichar <<= UTF8_V_SHIFT;
		unichar |= *s++ & 0x3F;
		unichar <<= UTF8_V_SHIFT;
		unichar |= *s++ & 0x3F;
		unichar <<= UTF8_V_SHIFT;
		unichar |= *s & 0x3F;
	}
	return unichar;
}