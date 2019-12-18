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
typedef  int uint16_t ;
typedef  int uchar_t ;

/* Variables and functions */

__attribute__((used)) static bool from_surrogate_pair(uint16_t uc, uint16_t lc, uchar_t *unicode)
{
	if (uc >= 0xD800 && uc <= 0xDBFF && lc >= 0xDC00 && lc <= 0xDFFF) {
		*unicode = 0x10000 + ((((uchar_t)uc & 0x3FF) << 10) | (lc & 0x3FF));
		return true;
	} else {
		return false;
	}
}