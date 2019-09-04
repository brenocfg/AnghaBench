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

__attribute__((used)) static int utf8_validate_cz(const char *s)
{
	unsigned char c = *s++;
	
	if (c <= 0x7F) {        /* 00..7F */
		return 1;
	} else if (c <= 0xC1) { /* 80..C1 */
		/* Disallow overlong 2-byte sequence. */
		return 0;
	} else if (c <= 0xDF) { /* C2..DF */
		/* Make sure subsequent byte is in the range 0x80..0xBF. */
		if (((unsigned char)*s++ & 0xC0) != 0x80)
			return 0;
		
		return 2;
	} else if (c <= 0xEF) { /* E0..EF */
		/* Disallow overlong 3-byte sequence. */
		if (c == 0xE0 && (unsigned char)*s < 0xA0)
			return 0;
		
		/* Disallow U+D800..U+DFFF. */
		if (c == 0xED && (unsigned char)*s > 0x9F)
			return 0;
		
		/* Make sure subsequent bytes are in the range 0x80..0xBF. */
		if (((unsigned char)*s++ & 0xC0) != 0x80)
			return 0;
		if (((unsigned char)*s++ & 0xC0) != 0x80)
			return 0;
		
		return 3;
	} else if (c <= 0xF4) { /* F0..F4 */
		/* Disallow overlong 4-byte sequence. */
		if (c == 0xF0 && (unsigned char)*s < 0x90)
			return 0;
		
		/* Disallow codepoints beyond U+10FFFF. */
		if (c == 0xF4 && (unsigned char)*s > 0x8F)
			return 0;
		
		/* Make sure subsequent bytes are in the range 0x80..0xBF. */
		if (((unsigned char)*s++ & 0xC0) != 0x80)
			return 0;
		if (((unsigned char)*s++ & 0xC0) != 0x80)
			return 0;
		if (((unsigned char)*s++ & 0xC0) != 0x80)
			return 0;
		
		return 4;
	} else {                /* F5..FF */
		return 0;
	}
}