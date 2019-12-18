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
typedef  int /*<<< orphan*/  uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  conv18030 (int,int,int) ; 

__attribute__((used)) static uint32
conv_18030_to_utf8(uint32 code)
{
#define conv18030(minunicode, mincode, maxcode) \
	if (code >= mincode && code <= maxcode) \
		return unicode_to_utf8word(gb_linear(code) - gb_linear(mincode) + minunicode)

	conv18030(0x0452, 0x8130D330, 0x8136A531);
	conv18030(0x2643, 0x8137A839, 0x8138FD38);
	conv18030(0x361B, 0x8230A633, 0x8230F237);
	conv18030(0x3CE1, 0x8231D438, 0x8232AF32);
	conv18030(0x4160, 0x8232C937, 0x8232F837);
	conv18030(0x44D7, 0x8233A339, 0x8233C931);
	conv18030(0x478E, 0x8233E838, 0x82349638);
	conv18030(0x49B8, 0x8234A131, 0x8234E733);
	conv18030(0x9FA6, 0x82358F33, 0x8336C738);
	conv18030(0xE865, 0x8336D030, 0x84308534);
	conv18030(0xFA2A, 0x84309C38, 0x84318537);
	conv18030(0xFFE6, 0x8431A234, 0x8431A439);
	conv18030(0x10000, 0x90308130, 0xE3329A35);
	/* No mapping exists */
	return 0;
}