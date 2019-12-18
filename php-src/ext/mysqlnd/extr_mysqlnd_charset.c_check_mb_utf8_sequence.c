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
typedef  int zend_uchar ;

/* Variables and functions */

__attribute__((used)) static unsigned int check_mb_utf8_sequence(const char * const start, const char * const end)
{
	zend_uchar	c;

	if (start >= end) {
		return 0;
	}

	c = (zend_uchar) start[0];

	if (c < 0x80) {
		return 1;		/* single byte character */
	}
	if (c < 0xC2) {
		return 0;		/* invalid mb character */
	}
	if (c < 0xE0) {
		if (start + 2 > end) {
			return 0;	/* too small */
		}
		if (!(((zend_uchar)start[1] ^ 0x80) < 0x40)) {
			return 0;
		}
		return 2;
	}
	if (c < 0xF0) {
		if (start + 3 > end) {
			return 0;	/* too small */
		}
		if (!(((zend_uchar)start[1] ^ 0x80) < 0x40 && ((zend_uchar)start[2] ^ 0x80) < 0x40 &&
			(c >= 0xE1 || (zend_uchar)start[1] >= 0xA0))) {
			return 0;	/* invalid utf8 character */
		}
		return 3;
	}
	if (c < 0xF5) {
		if (start + 4 > end) { /* We need 4 characters */
			return 0;	/* too small */
		}

		/*
		  UTF-8 quick four-byte mask:
		  11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
		  Encoding allows to encode U+00010000..U+001FFFFF

		  The maximum character defined in the Unicode standard is U+0010FFFF.
		  Higher characters U+00110000..U+001FFFFF are not used.

		  11110000.10010000.10xxxxxx.10xxxxxx == F0.90.80.80 == U+00010000 (min)
		  11110100.10001111.10111111.10111111 == F4.8F.BF.BF == U+0010FFFF (max)

		  Valid codes:
		  [F0][90..BF][80..BF][80..BF]
		  [F1][80..BF][80..BF][80..BF]
		  [F2][80..BF][80..BF][80..BF]
		  [F3][80..BF][80..BF][80..BF]
		  [F4][80..8F][80..BF][80..BF]
		*/

		if (!(((zend_uchar)start[1] ^ 0x80) < 0x40 &&
			((zend_uchar)start[2] ^ 0x80) < 0x40 &&
			((zend_uchar)start[3] ^ 0x80) < 0x40 &&
				(c >= 0xf1 || (zend_uchar)start[1] >= 0x90) &&
				(c <= 0xf3 || (zend_uchar)start[1] <= 0x8F)))
		{
			return 0;	/* invalid utf8 character */
		}
		return 4;
	}
	return 0;
}