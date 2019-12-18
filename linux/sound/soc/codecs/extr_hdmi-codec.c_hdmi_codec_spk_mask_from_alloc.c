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
 int ARRAY_SIZE (unsigned long const*) ; 
#define  FC 138 
#define  FL 137 
#define  FLC 136 
#define  FR 135 
#define  FRC 134 
#define  LFE 133 
#define  RC 132 
#define  RL 131 
#define  RLC 130 
#define  RR 129 
#define  RRC 128 

__attribute__((used)) static unsigned long hdmi_codec_spk_mask_from_alloc(int spk_alloc)
{
	int i;
	static const unsigned long hdmi_codec_eld_spk_alloc_bits[] = {
		[0] = FL | FR, [1] = LFE, [2] = FC, [3] = RL | RR,
		[4] = RC, [5] = FLC | FRC, [6] = RLC | RRC,
	};
	unsigned long spk_mask = 0;

	for (i = 0; i < ARRAY_SIZE(hdmi_codec_eld_spk_alloc_bits); i++) {
		if (spk_alloc & (1 << i))
			spk_mask |= hdmi_codec_eld_spk_alloc_bits[i];
	}

	return spk_mask;
}