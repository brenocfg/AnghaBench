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
 int /*<<< orphan*/  IS_SJIS_NECIBM (unsigned char const,unsigned char const) ; 

__attribute__((used)) static inline int sjisnec2sjisibm(unsigned char *sjisibm,
				  const unsigned char sjisnec_hi,
				  const unsigned char sjisnec_lo)
{
	int count;

	if (! IS_SJIS_NECIBM(sjisnec_hi, sjisnec_lo))
		return 0;

	if ((sjisnec_hi == 0xEE) && (sjisnec_lo == 0xF9)) {
		sjisibm[0] = 0x81;
		sjisibm[1] = 0xCA;
		return 2;
	}

	if ((sjisnec_hi == 0xEE) && (sjisnec_lo >= 0xEF)) {
		count = (sjisnec_hi << 8 | sjisnec_lo)
			- (sjisnec_lo <= 0xF9 ? 0xEEEF : (0xEEEF - 10));
	} else {
		count = (sjisnec_hi - 0xED) * (0xFC - 0x40)
			+ (sjisnec_lo - 0x40) + (0x5C - 0x40);
		if (sjisnec_lo >= 0x7F)
			count--;
	}

	sjisibm[0] = 0xFA + (count / (0xFC - 0x40));
	sjisibm[1] = 0x40 + (count % (0xFC - 0x40));
	if (sjisibm[1] >= 0x7F)
		sjisibm[1]++;

	return 2;
}