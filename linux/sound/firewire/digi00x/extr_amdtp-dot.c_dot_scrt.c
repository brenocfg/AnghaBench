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
typedef  int u8 ;

/* Variables and functions */

__attribute__((used)) static u8 dot_scrt(const u8 idx, const unsigned int off)
{
	/*
	 * the length of the added pattern only depends on the lower nibble
	 * of the last non-zero data
	 */
	static const u8 len[16] = {0, 1, 3, 5, 7, 9, 11, 13, 14,
				   12, 10, 8, 6, 4, 2, 0};

	/*
	 * the lower nibble of the salt. Interleaved sequence.
	 * this is walked backwards according to len[]
	 */
	static const u8 nib[15] = {0x8, 0x7, 0x9, 0x6, 0xa, 0x5, 0xb, 0x4,
				   0xc, 0x3, 0xd, 0x2, 0xe, 0x1, 0xf};

	/* circular list for the salt's hi nibble. */
	static const u8 hir[15] = {0x0, 0x6, 0xf, 0x8, 0x7, 0x5, 0x3, 0x4,
				   0xc, 0xd, 0xe, 0x1, 0x2, 0xb, 0xa};

	/*
	 * start offset for upper nibble mapping.
	 * note: 9 is /special/. In the case where the high nibble == 0x9,
	 * hir[] is not used and - coincidentally - the salt's hi nibble is
	 * 0x09 regardless of the offset.
	 */
	static const u8 hio[16] = {0, 11, 12, 6, 7, 5, 1, 4,
				   3, 0x00, 14, 13, 8, 9, 10, 2};

	const u8 ln = idx & 0xf;
	const u8 hn = (idx >> 4) & 0xf;
	const u8 hr = (hn == 0x9) ? 0x9 : hir[(hio[hn] + off) % 15];

	if (len[ln] < off)
		return 0x00;

	return ((nib[14 + off - len[ln]]) | (hr << 4));
}