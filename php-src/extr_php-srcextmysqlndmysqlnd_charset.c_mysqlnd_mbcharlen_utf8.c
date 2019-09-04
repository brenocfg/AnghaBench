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

__attribute__((used)) static unsigned int mysqlnd_mbcharlen_utf8(const unsigned int utf8)
{
	if (utf8 < 0x80) {
		return 1;		/* single byte character */
	}
	if (utf8 < 0xC2) {
		return 0;		/* invalid multibyte header */
	}
	if (utf8 < 0xE0) {
		return 2;		/* double byte character */
	}
	if (utf8 < 0xF0) {
		return 3;		/* triple byte character */
	}
	if (utf8 < 0xF8) {
		return 4;		/* four byte character */
	}
	return 0;
}