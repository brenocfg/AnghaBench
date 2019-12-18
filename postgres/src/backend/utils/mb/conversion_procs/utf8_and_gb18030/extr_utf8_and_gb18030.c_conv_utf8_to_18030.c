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
 int /*<<< orphan*/  convutf8 (int,int,int) ; 
 int /*<<< orphan*/  utf8word_to_unicode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32
conv_utf8_to_18030(uint32 code)
{
	uint32		ucs = utf8word_to_unicode(code);

#define convutf8(minunicode, maxunicode, mincode) \
	if (ucs >= minunicode && ucs <= maxunicode) \
		return gb_unlinear(ucs - minunicode + gb_linear(mincode))

	convutf8(0x0452, 0x200F, 0x8130D330);
	convutf8(0x2643, 0x2E80, 0x8137A839);
	convutf8(0x361B, 0x3917, 0x8230A633);
	convutf8(0x3CE1, 0x4055, 0x8231D438);
	convutf8(0x4160, 0x4336, 0x8232C937);
	convutf8(0x44D7, 0x464B, 0x8233A339);
	convutf8(0x478E, 0x4946, 0x8233E838);
	convutf8(0x49B8, 0x4C76, 0x8234A131);
	convutf8(0x9FA6, 0xD7FF, 0x82358F33);
	convutf8(0xE865, 0xF92B, 0x8336D030);
	convutf8(0xFA2A, 0xFE2F, 0x84309C38);
	convutf8(0xFFE6, 0xFFFF, 0x8431A234);
	convutf8(0x10000, 0x10FFFF, 0x90308130);
	/* No mapping exists */
	return 0;
}