#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  mmio; } ;
typedef  TYPE_1__ vortex_t ;

/* Variables and functions */
 int EN_SPDIF ; 
 scalar_t__ VORTEX_CODEC_EN ; 
 scalar_t__ VORTEX_SPDIF_CFG0 ; 
 scalar_t__ VORTEX_SPDIF_CFG1 ; 
 scalar_t__ VORTEX_SPDIF_FLAGS ; 
 scalar_t__ VORTEX_SPDIF_SMPRATE ; 
 int hwread (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  hwwrite (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  vortex_src_setupchannel (TYPE_1__*,int,int,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void vortex_spdif_init(vortex_t * vortex, int spdif_sr, int spdif_mode)
{
	int i, this_38 = 0, this_04 = 0, this_08 = 0, this_0c = 0;

	/* CAsp4Spdif::InitializeSpdifHardware(void) */
	hwwrite(vortex->mmio, VORTEX_SPDIF_FLAGS,
		hwread(vortex->mmio, VORTEX_SPDIF_FLAGS) & 0xfff3fffd);
	//for (i=0x291D4; i<0x29200; i+=4)
	for (i = 0; i < 11; i++)
		hwwrite(vortex->mmio, VORTEX_SPDIF_CFG1 + (i << 2), 0);
	//hwwrite(vortex->mmio, 0x29190, hwread(vortex->mmio, 0x29190) | 0xc0000);
	hwwrite(vortex->mmio, VORTEX_CODEC_EN,
		hwread(vortex->mmio, VORTEX_CODEC_EN) | EN_SPDIF);

	/* CAsp4Spdif::ProgramSRCInHardware(enum  SPDIF_SR,enum  SPDIFMODE) */
	if (this_04 && this_08) {
		int edi;

		i = (((0x5DC00000 / spdif_sr) + 1) >> 1);
		if (i > 0x800) {
			if (i < 0x1ffff)
				edi = (i >> 1);
			else
				edi = 0x1ffff;
		} else {
			edi = 0x800;
		}
		/* this_04 and this_08 are the CASp4Src's (samplerate converters) */
		vortex_src_setupchannel(vortex, this_04, edi, 0, 1,
					this_0c, 1, 0, edi, 1);
		vortex_src_setupchannel(vortex, this_08, edi, 0, 1,
					this_0c, 1, 0, edi, 1);
	}

	i = spdif_sr;
	spdif_sr |= 0x8c;
	switch (i) {
	case 32000:
		this_38 &= 0xFFFFFFFE;
		this_38 &= 0xFFFFFFFD;
		this_38 &= 0xF3FFFFFF;
		this_38 |= 0x03000000;	/* set 32khz samplerate */
		this_38 &= 0xFFFFFF3F;
		spdif_sr &= 0xFFFFFFFD;
		spdif_sr |= 1;
		break;
	case 44100:
		this_38 &= 0xFFFFFFFE;
		this_38 &= 0xFFFFFFFD;
		this_38 &= 0xF0FFFFFF;
		this_38 |= 0x03000000;
		this_38 &= 0xFFFFFF3F;
		spdif_sr &= 0xFFFFFFFC;
		break;
	case 48000:
		if (spdif_mode == 1) {
			this_38 &= 0xFFFFFFFE;
			this_38 &= 0xFFFFFFFD;
			this_38 &= 0xF2FFFFFF;
			this_38 |= 0x02000000;	/* set 48khz samplerate */
			this_38 &= 0xFFFFFF3F;
		} else {
			/* J. Gordon Wolfe: I think this stuff is for AC3 */
			this_38 |= 0x00000003;
			this_38 &= 0xFFFFFFBF;
			this_38 |= 0x80;
		}
		spdif_sr |= 2;
		spdif_sr &= 0xFFFFFFFE;
		break;

	}
	/* looks like the next 2 lines transfer a 16-bit value into 2 8-bit 
	   registers. seems to be for the standard IEC/SPDIF initialization 
	   stuff */
	hwwrite(vortex->mmio, VORTEX_SPDIF_CFG0, this_38 & 0xffff);
	hwwrite(vortex->mmio, VORTEX_SPDIF_CFG1, this_38 >> 0x10);
	hwwrite(vortex->mmio, VORTEX_SPDIF_SMPRATE, spdif_sr);
}