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
typedef  int uchar_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int utf8_write_char(uchar_t unicode, char *out)
{
	unsigned char *o = (unsigned char*) out;
	
	assert(unicode <= 0x10FFFF && !(unicode >= 0xD800 && unicode <= 0xDFFF));

	if (unicode <= 0x7F) {
		/* U+0000..U+007F */
		*o++ = (unsigned char)unicode;
		return 1;
	} else if (unicode <= 0x7FF) {
		/* U+0080..U+07FF */
		*o++ = (unsigned char)(0xC0 | unicode >> 6);
		*o++ = (unsigned char)(0x80 | (unicode & 0x3F));
		return 2;
	} else if (unicode <= 0xFFFF) {
		/* U+0800..U+FFFF */
		*o++ = (unsigned char)(0xE0 | unicode >> 12);
		*o++ = (unsigned char)(0x80 | (unicode >> 6 & 0x3F));
		*o++ = (unsigned char)(0x80 | (unicode & 0x3F));
		return 3;
	} else {
		/* U+10000..U+10FFFF */
		*o++ = (unsigned char)(0xF0 | unicode >> 18);
		*o++ = (unsigned char)(0x80 | (unicode >> 12 & 0x3F));
		*o++ = (unsigned char)(0x80 | (unicode >> 6 & 0x3F));
		*o++ = (unsigned char)(0x80 | (unicode & 0x3F));
		return 4;
	}
}