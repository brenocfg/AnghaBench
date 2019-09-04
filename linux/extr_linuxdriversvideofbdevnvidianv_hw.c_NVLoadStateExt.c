#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nvidia_par {scalar_t__ Architecture; int Chipset; int FbMapSize; int FbUsableSize; int FbAddress; int PanelTweak; TYPE_1__* CurrentState; int /*<<< orphan*/ * PCRTC; int /*<<< orphan*/ * PRAMDAC; int /*<<< orphan*/ * PRAMDAC0; scalar_t__ twoStagePLL; scalar_t__ twoHeads; scalar_t__ FlatPanel; int /*<<< orphan*/  PCIO; int /*<<< orphan*/ * PMC; int /*<<< orphan*/ * PCRTC0; int /*<<< orphan*/ * PFIFO; int /*<<< orphan*/ * PGRAPH; int /*<<< orphan*/ * PFB; int /*<<< orphan*/ * REGS; int /*<<< orphan*/ * PRAMIN; scalar_t__ WaitVSyncPossible; int /*<<< orphan*/ * PTIMER; } ;
struct TYPE_3__ {int config; int head; int head2; int cursorConfig; int displayV; int dither; int timingH; int timingV; int extra; int repaint0; int repaint1; int screen; int pixel; int horiz; int fifo; int arbitration0; int arbitration1; int cursor0; int cursor1; int cursor2; int interlace; int control; int pllsel; int vpll; int vpll2; int vpllB; int vpll2B; int scale; int crtcSync; int general; } ;
typedef  TYPE_1__ RIVA_HW_STATE ;

/* Variables and functions */
 scalar_t__ NV_ARCH_04 ; 
 scalar_t__ NV_ARCH_10 ; 
 scalar_t__ NV_ARCH_30 ; 
 scalar_t__ NV_ARCH_40 ; 
 int NV_RD32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  NV_WR32 (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  VGA_WR08 (int /*<<< orphan*/ ,int,int) ; 

void NVLoadStateExt(struct nvidia_par *par, RIVA_HW_STATE * state)
{
	int i, j;

	NV_WR32(par->PMC, 0x0140, 0x00000000);
	NV_WR32(par->PMC, 0x0200, 0xFFFF00FF);
	NV_WR32(par->PMC, 0x0200, 0xFFFFFFFF);

	NV_WR32(par->PTIMER, 0x0200 * 4, 0x00000008);
	NV_WR32(par->PTIMER, 0x0210 * 4, 0x00000003);
	NV_WR32(par->PTIMER, 0x0140 * 4, 0x00000000);
	NV_WR32(par->PTIMER, 0x0100 * 4, 0xFFFFFFFF);

	if (par->Architecture == NV_ARCH_04) {
		if (state)
			NV_WR32(par->PFB, 0x0200, state->config);
	} else if ((par->Architecture < NV_ARCH_40) ||
		   (par->Chipset & 0xfff0) == 0x0040) {
		for (i = 0; i < 8; i++) {
			NV_WR32(par->PFB, 0x0240 + (i * 0x10), 0);
			NV_WR32(par->PFB, 0x0244 + (i * 0x10),
				par->FbMapSize - 1);
		}
	} else {
		int regions = 12;

		if (((par->Chipset & 0xfff0) == 0x0090) ||
		    ((par->Chipset & 0xfff0) == 0x01D0) ||
		    ((par->Chipset & 0xfff0) == 0x0290) ||
		    ((par->Chipset & 0xfff0) == 0x0390) ||
		    ((par->Chipset & 0xfff0) == 0x03D0))
			regions = 15;
		for(i = 0; i < regions; i++) {
			NV_WR32(par->PFB, 0x0600 + (i * 0x10), 0);
			NV_WR32(par->PFB, 0x0604 + (i * 0x10),
				par->FbMapSize - 1);
		}
	}

	if (par->Architecture >= NV_ARCH_40) {
		NV_WR32(par->PRAMIN, 0x0000 * 4, 0x80000010);
		NV_WR32(par->PRAMIN, 0x0001 * 4, 0x00101202);
		NV_WR32(par->PRAMIN, 0x0002 * 4, 0x80000011);
		NV_WR32(par->PRAMIN, 0x0003 * 4, 0x00101204);
		NV_WR32(par->PRAMIN, 0x0004 * 4, 0x80000012);
		NV_WR32(par->PRAMIN, 0x0005 * 4, 0x00101206);
		NV_WR32(par->PRAMIN, 0x0006 * 4, 0x80000013);
		NV_WR32(par->PRAMIN, 0x0007 * 4, 0x00101208);
		NV_WR32(par->PRAMIN, 0x0008 * 4, 0x80000014);
		NV_WR32(par->PRAMIN, 0x0009 * 4, 0x0010120A);
		NV_WR32(par->PRAMIN, 0x000A * 4, 0x80000015);
		NV_WR32(par->PRAMIN, 0x000B * 4, 0x0010120C);
		NV_WR32(par->PRAMIN, 0x000C * 4, 0x80000016);
		NV_WR32(par->PRAMIN, 0x000D * 4, 0x0010120E);
		NV_WR32(par->PRAMIN, 0x000E * 4, 0x80000017);
		NV_WR32(par->PRAMIN, 0x000F * 4, 0x00101210);
		NV_WR32(par->PRAMIN, 0x0800 * 4, 0x00003000);
		NV_WR32(par->PRAMIN, 0x0801 * 4, par->FbMapSize - 1);
		NV_WR32(par->PRAMIN, 0x0802 * 4, 0x00000002);
		NV_WR32(par->PRAMIN, 0x0808 * 4, 0x02080062);
		NV_WR32(par->PRAMIN, 0x0809 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x080A * 4, 0x00001200);
		NV_WR32(par->PRAMIN, 0x080B * 4, 0x00001200);
		NV_WR32(par->PRAMIN, 0x080C * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x080D * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0810 * 4, 0x02080043);
		NV_WR32(par->PRAMIN, 0x0811 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0812 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0813 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0814 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0815 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0818 * 4, 0x02080044);
		NV_WR32(par->PRAMIN, 0x0819 * 4, 0x02000000);
		NV_WR32(par->PRAMIN, 0x081A * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x081B * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x081C * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x081D * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0820 * 4, 0x02080019);
		NV_WR32(par->PRAMIN, 0x0821 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0822 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0823 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0824 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0825 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0828 * 4, 0x020A005C);
		NV_WR32(par->PRAMIN, 0x0829 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x082A * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x082B * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x082C * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x082D * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0830 * 4, 0x0208009F);
		NV_WR32(par->PRAMIN, 0x0831 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0832 * 4, 0x00001200);
		NV_WR32(par->PRAMIN, 0x0833 * 4, 0x00001200);
		NV_WR32(par->PRAMIN, 0x0834 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0835 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0838 * 4, 0x0208004A);
		NV_WR32(par->PRAMIN, 0x0839 * 4, 0x02000000);
		NV_WR32(par->PRAMIN, 0x083A * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x083B * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x083C * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x083D * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0840 * 4, 0x02080077);
		NV_WR32(par->PRAMIN, 0x0841 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0842 * 4, 0x00001200);
		NV_WR32(par->PRAMIN, 0x0843 * 4, 0x00001200);
		NV_WR32(par->PRAMIN, 0x0844 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0845 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x084C * 4, 0x00003002);
		NV_WR32(par->PRAMIN, 0x084D * 4, 0x00007FFF);
		NV_WR32(par->PRAMIN, 0x084E * 4,
			par->FbUsableSize | 0x00000002);

#ifdef __BIG_ENDIAN
		NV_WR32(par->PRAMIN, 0x080A * 4,
			NV_RD32(par->PRAMIN, 0x080A * 4) | 0x01000000);
		NV_WR32(par->PRAMIN, 0x0812 * 4,
			NV_RD32(par->PRAMIN, 0x0812 * 4) | 0x01000000);
		NV_WR32(par->PRAMIN, 0x081A * 4,
			NV_RD32(par->PRAMIN, 0x081A * 4) | 0x01000000);
		NV_WR32(par->PRAMIN, 0x0822 * 4,
			NV_RD32(par->PRAMIN, 0x0822 * 4) | 0x01000000);
		NV_WR32(par->PRAMIN, 0x082A * 4,
			NV_RD32(par->PRAMIN, 0x082A * 4) | 0x01000000);
		NV_WR32(par->PRAMIN, 0x0832 * 4,
			NV_RD32(par->PRAMIN, 0x0832 * 4) | 0x01000000);
		NV_WR32(par->PRAMIN, 0x083A * 4,
			NV_RD32(par->PRAMIN, 0x083A * 4) | 0x01000000);
		NV_WR32(par->PRAMIN, 0x0842 * 4,
			NV_RD32(par->PRAMIN, 0x0842 * 4) | 0x01000000);
		NV_WR32(par->PRAMIN, 0x0819 * 4, 0x01000000);
		NV_WR32(par->PRAMIN, 0x0839 * 4, 0x01000000);
#endif
	} else {
		NV_WR32(par->PRAMIN, 0x0000 * 4, 0x80000010);
		NV_WR32(par->PRAMIN, 0x0001 * 4, 0x80011201);
		NV_WR32(par->PRAMIN, 0x0002 * 4, 0x80000011);
		NV_WR32(par->PRAMIN, 0x0003 * 4, 0x80011202);
		NV_WR32(par->PRAMIN, 0x0004 * 4, 0x80000012);
		NV_WR32(par->PRAMIN, 0x0005 * 4, 0x80011203);
		NV_WR32(par->PRAMIN, 0x0006 * 4, 0x80000013);
		NV_WR32(par->PRAMIN, 0x0007 * 4, 0x80011204);
		NV_WR32(par->PRAMIN, 0x0008 * 4, 0x80000014);
		NV_WR32(par->PRAMIN, 0x0009 * 4, 0x80011205);
		NV_WR32(par->PRAMIN, 0x000A * 4, 0x80000015);
		NV_WR32(par->PRAMIN, 0x000B * 4, 0x80011206);
		NV_WR32(par->PRAMIN, 0x000C * 4, 0x80000016);
		NV_WR32(par->PRAMIN, 0x000D * 4, 0x80011207);
		NV_WR32(par->PRAMIN, 0x000E * 4, 0x80000017);
		NV_WR32(par->PRAMIN, 0x000F * 4, 0x80011208);
		NV_WR32(par->PRAMIN, 0x0800 * 4, 0x00003000);
		NV_WR32(par->PRAMIN, 0x0801 * 4, par->FbMapSize - 1);
		NV_WR32(par->PRAMIN, 0x0802 * 4, 0x00000002);
		NV_WR32(par->PRAMIN, 0x0803 * 4, 0x00000002);
		if (par->Architecture >= NV_ARCH_10)
			NV_WR32(par->PRAMIN, 0x0804 * 4, 0x01008062);
		else
			NV_WR32(par->PRAMIN, 0x0804 * 4, 0x01008042);
		NV_WR32(par->PRAMIN, 0x0805 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0806 * 4, 0x12001200);
		NV_WR32(par->PRAMIN, 0x0807 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0808 * 4, 0x01008043);
		NV_WR32(par->PRAMIN, 0x0809 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x080A * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x080B * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x080C * 4, 0x01008044);
		NV_WR32(par->PRAMIN, 0x080D * 4, 0x00000002);
		NV_WR32(par->PRAMIN, 0x080E * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x080F * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0810 * 4, 0x01008019);
		NV_WR32(par->PRAMIN, 0x0811 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0812 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0813 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0814 * 4, 0x0100A05C);
		NV_WR32(par->PRAMIN, 0x0815 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0816 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0817 * 4, 0x00000000);
		if (par->WaitVSyncPossible)
			NV_WR32(par->PRAMIN, 0x0818 * 4, 0x0100809F);
		else
			NV_WR32(par->PRAMIN, 0x0818 * 4, 0x0100805F);
		NV_WR32(par->PRAMIN, 0x0819 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x081A * 4, 0x12001200);
		NV_WR32(par->PRAMIN, 0x081B * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x081C * 4, 0x0100804A);
		NV_WR32(par->PRAMIN, 0x081D * 4, 0x00000002);
		NV_WR32(par->PRAMIN, 0x081E * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x081F * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0820 * 4, 0x01018077);
		NV_WR32(par->PRAMIN, 0x0821 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0822 * 4, 0x12001200);
		NV_WR32(par->PRAMIN, 0x0823 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0824 * 4, 0x00003002);
		NV_WR32(par->PRAMIN, 0x0825 * 4, 0x00007FFF);
		NV_WR32(par->PRAMIN, 0x0826 * 4,
			par->FbUsableSize | 0x00000002);
		NV_WR32(par->PRAMIN, 0x0827 * 4, 0x00000002);
#ifdef __BIG_ENDIAN
		NV_WR32(par->PRAMIN, 0x0804 * 4,
			NV_RD32(par->PRAMIN, 0x0804 * 4) | 0x00080000);
		NV_WR32(par->PRAMIN, 0x0808 * 4,
			NV_RD32(par->PRAMIN, 0x0808 * 4) | 0x00080000);
		NV_WR32(par->PRAMIN, 0x080C * 4,
			NV_RD32(par->PRAMIN, 0x080C * 4) | 0x00080000);
		NV_WR32(par->PRAMIN, 0x0810 * 4,
			NV_RD32(par->PRAMIN, 0x0810 * 4) | 0x00080000);
		NV_WR32(par->PRAMIN, 0x0814 * 4,
			NV_RD32(par->PRAMIN, 0x0814 * 4) | 0x00080000);
		NV_WR32(par->PRAMIN, 0x0818 * 4,
			NV_RD32(par->PRAMIN, 0x0818 * 4) | 0x00080000);
		NV_WR32(par->PRAMIN, 0x081C * 4,
			NV_RD32(par->PRAMIN, 0x081C * 4) | 0x00080000);
		NV_WR32(par->PRAMIN, 0x0820 * 4,
			NV_RD32(par->PRAMIN, 0x0820 * 4) | 0x00080000);
		NV_WR32(par->PRAMIN, 0x080D * 4, 0x00000001);
		NV_WR32(par->PRAMIN, 0x081D * 4, 0x00000001);
#endif
	}
	if (par->Architecture < NV_ARCH_10) {
		if ((par->Chipset & 0x0fff) == 0x0020) {
			NV_WR32(par->PRAMIN, 0x0824 * 4,
				NV_RD32(par->PRAMIN, 0x0824 * 4) | 0x00020000);
			NV_WR32(par->PRAMIN, 0x0826 * 4,
				NV_RD32(par->PRAMIN,
					0x0826 * 4) + par->FbAddress);
		}
		NV_WR32(par->PGRAPH, 0x0080, 0x000001FF);
		NV_WR32(par->PGRAPH, 0x0080, 0x1230C000);
		NV_WR32(par->PGRAPH, 0x0084, 0x72111101);
		NV_WR32(par->PGRAPH, 0x0088, 0x11D5F071);
		NV_WR32(par->PGRAPH, 0x008C, 0x0004FF31);
		NV_WR32(par->PGRAPH, 0x008C, 0x4004FF31);
		NV_WR32(par->PGRAPH, 0x0140, 0x00000000);
		NV_WR32(par->PGRAPH, 0x0100, 0xFFFFFFFF);
		NV_WR32(par->PGRAPH, 0x0170, 0x10010100);
		NV_WR32(par->PGRAPH, 0x0710, 0xFFFFFFFF);
		NV_WR32(par->PGRAPH, 0x0720, 0x00000001);
		NV_WR32(par->PGRAPH, 0x0810, 0x00000000);
		NV_WR32(par->PGRAPH, 0x0608, 0xFFFFFFFF);
	} else {
		NV_WR32(par->PGRAPH, 0x0080, 0xFFFFFFFF);
		NV_WR32(par->PGRAPH, 0x0080, 0x00000000);

		NV_WR32(par->PGRAPH, 0x0140, 0x00000000);
		NV_WR32(par->PGRAPH, 0x0100, 0xFFFFFFFF);
		NV_WR32(par->PGRAPH, 0x0144, 0x10010100);
		NV_WR32(par->PGRAPH, 0x0714, 0xFFFFFFFF);
		NV_WR32(par->PGRAPH, 0x0720, 0x00000001);
		NV_WR32(par->PGRAPH, 0x0710,
			NV_RD32(par->PGRAPH, 0x0710) & 0x0007ff00);
		NV_WR32(par->PGRAPH, 0x0710,
			NV_RD32(par->PGRAPH, 0x0710) | 0x00020100);

		if (par->Architecture == NV_ARCH_10) {
			NV_WR32(par->PGRAPH, 0x0084, 0x00118700);
			NV_WR32(par->PGRAPH, 0x0088, 0x24E00810);
			NV_WR32(par->PGRAPH, 0x008C, 0x55DE0030);

			for (i = 0; i < 32; i++)
				NV_WR32(&par->PGRAPH[(0x0B00 / 4) + i], 0,
					NV_RD32(&par->PFB[(0x0240 / 4) + i],
						0));

			NV_WR32(par->PGRAPH, 0x640, 0);
			NV_WR32(par->PGRAPH, 0x644, 0);
			NV_WR32(par->PGRAPH, 0x684, par->FbMapSize - 1);
			NV_WR32(par->PGRAPH, 0x688, par->FbMapSize - 1);

			NV_WR32(par->PGRAPH, 0x0810, 0x00000000);
			NV_WR32(par->PGRAPH, 0x0608, 0xFFFFFFFF);
		} else {
			if (par->Architecture >= NV_ARCH_40) {
				NV_WR32(par->PGRAPH, 0x0084, 0x401287c0);
				NV_WR32(par->PGRAPH, 0x008C, 0x60de8051);
				NV_WR32(par->PGRAPH, 0x0090, 0x00008000);
				NV_WR32(par->PGRAPH, 0x0610, 0x00be3c5f);
				NV_WR32(par->PGRAPH, 0x0bc4,
					NV_RD32(par->PGRAPH, 0x0bc4) |
					0x00008000);

				j = NV_RD32(par->REGS, 0x1540) & 0xff;

				if (j) {
					for (i = 0; !(j & 1); j >>= 1, i++);
					NV_WR32(par->PGRAPH, 0x5000, i);
				}

				if ((par->Chipset & 0xfff0) == 0x0040) {
					NV_WR32(par->PGRAPH, 0x09b0,
						0x83280fff);
					NV_WR32(par->PGRAPH, 0x09b4,
						0x000000a0);
				} else {
					NV_WR32(par->PGRAPH, 0x0820,
						0x83280eff);
					NV_WR32(par->PGRAPH, 0x0824,
						0x000000a0);
				}

				switch (par->Chipset & 0xfff0) {
				case 0x0040:
				case 0x0210:
					NV_WR32(par->PGRAPH, 0x09b8,
						0x0078e366);
					NV_WR32(par->PGRAPH, 0x09bc,
						0x0000014c);
					NV_WR32(par->PFB, 0x033C,
						NV_RD32(par->PFB, 0x33C) &
						0xffff7fff);
					break;
				case 0x00C0:
				case 0x0120:
					NV_WR32(par->PGRAPH, 0x0828,
						0x007596ff);
					NV_WR32(par->PGRAPH, 0x082C,
						0x00000108);
					break;
				case 0x0160:
				case 0x01D0:
				case 0x0240:
				case 0x03D0:
					NV_WR32(par->PMC, 0x1700,
						NV_RD32(par->PFB, 0x020C));
					NV_WR32(par->PMC, 0x1704, 0);
					NV_WR32(par->PMC, 0x1708, 0);
					NV_WR32(par->PMC, 0x170C,
						NV_RD32(par->PFB, 0x020C));
					NV_WR32(par->PGRAPH, 0x0860, 0);
					NV_WR32(par->PGRAPH, 0x0864, 0);
					NV_WR32(par->PRAMDAC, 0x0608,
						NV_RD32(par->PRAMDAC,
							0x0608) | 0x00100000);
					break;
				case 0x0140:
					NV_WR32(par->PGRAPH, 0x0828,
						0x0072cb77);
					NV_WR32(par->PGRAPH, 0x082C,
						0x00000108);
					break;
				case 0x0220:
					NV_WR32(par->PGRAPH, 0x0860, 0);
					NV_WR32(par->PGRAPH, 0x0864, 0);
					NV_WR32(par->PRAMDAC, 0x0608,
						NV_RD32(par->PRAMDAC, 0x0608) |
						0x00100000);
					break;
				case 0x0090:
				case 0x0290:
				case 0x0390:
					NV_WR32(par->PRAMDAC, 0x0608,
						NV_RD32(par->PRAMDAC, 0x0608) |
						0x00100000);
					NV_WR32(par->PGRAPH, 0x0828,
						0x07830610);
					NV_WR32(par->PGRAPH, 0x082C,
						0x0000016A);
					break;
				default:
					break;
				}

				NV_WR32(par->PGRAPH, 0x0b38, 0x2ffff800);
				NV_WR32(par->PGRAPH, 0x0b3c, 0x00006000);
				NV_WR32(par->PGRAPH, 0x032C, 0x01000000);
				NV_WR32(par->PGRAPH, 0x0220, 0x00001200);
			} else if (par->Architecture == NV_ARCH_30) {
				NV_WR32(par->PGRAPH, 0x0084, 0x40108700);
				NV_WR32(par->PGRAPH, 0x0890, 0x00140000);
				NV_WR32(par->PGRAPH, 0x008C, 0xf00e0431);
				NV_WR32(par->PGRAPH, 0x0090, 0x00008000);
				NV_WR32(par->PGRAPH, 0x0610, 0xf04b1f36);
				NV_WR32(par->PGRAPH, 0x0B80, 0x1002d888);
				NV_WR32(par->PGRAPH, 0x0B88, 0x62ff007f);
			} else {
				NV_WR32(par->PGRAPH, 0x0084, 0x00118700);
				NV_WR32(par->PGRAPH, 0x008C, 0xF20E0431);
				NV_WR32(par->PGRAPH, 0x0090, 0x00000000);
				NV_WR32(par->PGRAPH, 0x009C, 0x00000040);

				if ((par->Chipset & 0x0ff0) >= 0x0250) {
					NV_WR32(par->PGRAPH, 0x0890,
						0x00080000);
					NV_WR32(par->PGRAPH, 0x0610,
						0x304B1FB6);
					NV_WR32(par->PGRAPH, 0x0B80,
						0x18B82880);
					NV_WR32(par->PGRAPH, 0x0B84,
						0x44000000);
					NV_WR32(par->PGRAPH, 0x0098,
						0x40000080);
					NV_WR32(par->PGRAPH, 0x0B88,
						0x000000ff);
				} else {
					NV_WR32(par->PGRAPH, 0x0880,
						0x00080000);
					NV_WR32(par->PGRAPH, 0x0094,
						0x00000005);
					NV_WR32(par->PGRAPH, 0x0B80,
						0x45CAA208);
					NV_WR32(par->PGRAPH, 0x0B84,
						0x24000000);
					NV_WR32(par->PGRAPH, 0x0098,
						0x00000040);
					NV_WR32(par->PGRAPH, 0x0750,
						0x00E00038);
					NV_WR32(par->PGRAPH, 0x0754,
						0x00000030);
					NV_WR32(par->PGRAPH, 0x0750,
						0x00E10038);
					NV_WR32(par->PGRAPH, 0x0754,
						0x00000030);
				}
			}

			if ((par->Architecture < NV_ARCH_40) ||
			    ((par->Chipset & 0xfff0) == 0x0040)) {
				for (i = 0; i < 32; i++) {
					NV_WR32(par->PGRAPH, 0x0900 + i*4,
						NV_RD32(par->PFB, 0x0240 +i*4));
					NV_WR32(par->PGRAPH, 0x6900 + i*4,
						NV_RD32(par->PFB, 0x0240 +i*4));
				}
			} else {
				if (((par->Chipset & 0xfff0) == 0x0090) ||
				    ((par->Chipset & 0xfff0) == 0x01D0) ||
				    ((par->Chipset & 0xfff0) == 0x0290) ||
				    ((par->Chipset & 0xfff0) == 0x0390) ||
				    ((par->Chipset & 0xfff0) == 0x03D0)) {
					for (i = 0; i < 60; i++) {
						NV_WR32(par->PGRAPH,
							0x0D00 + i*4,
							NV_RD32(par->PFB,
								0x0600 + i*4));
						NV_WR32(par->PGRAPH,
							0x6900 + i*4,
							NV_RD32(par->PFB,
								0x0600 + i*4));
					}
				} else {
					for (i = 0; i < 48; i++) {
						NV_WR32(par->PGRAPH,
							0x0900 + i*4,
							NV_RD32(par->PFB,
								0x0600 + i*4));
						if(((par->Chipset & 0xfff0)
						    != 0x0160) &&
						   ((par->Chipset & 0xfff0)
						    != 0x0220) &&
						   ((par->Chipset & 0xfff0)
						    != 0x240))
							NV_WR32(par->PGRAPH,
								0x6900 + i*4,
								NV_RD32(par->PFB,
									0x0600 + i*4));
					}
				}
			}

			if (par->Architecture >= NV_ARCH_40) {
				if ((par->Chipset & 0xfff0) == 0x0040) {
					NV_WR32(par->PGRAPH, 0x09A4,
						NV_RD32(par->PFB, 0x0200));
					NV_WR32(par->PGRAPH, 0x09A8,
						NV_RD32(par->PFB, 0x0204));
					NV_WR32(par->PGRAPH, 0x69A4,
						NV_RD32(par->PFB, 0x0200));
					NV_WR32(par->PGRAPH, 0x69A8,
						NV_RD32(par->PFB, 0x0204));

					NV_WR32(par->PGRAPH, 0x0820, 0);
					NV_WR32(par->PGRAPH, 0x0824, 0);
					NV_WR32(par->PGRAPH, 0x0864,
						par->FbMapSize - 1);
					NV_WR32(par->PGRAPH, 0x0868,
						par->FbMapSize - 1);
				} else {
					if ((par->Chipset & 0xfff0) == 0x0090 ||
					    (par->Chipset & 0xfff0) == 0x01D0 ||
					    (par->Chipset & 0xfff0) == 0x0290 ||
					    (par->Chipset & 0xfff0) == 0x0390) {
						NV_WR32(par->PGRAPH, 0x0DF0,
							NV_RD32(par->PFB, 0x0200));
						NV_WR32(par->PGRAPH, 0x0DF4,
							NV_RD32(par->PFB, 0x0204));
					} else {
						NV_WR32(par->PGRAPH, 0x09F0,
							NV_RD32(par->PFB, 0x0200));
						NV_WR32(par->PGRAPH, 0x09F4,
							NV_RD32(par->PFB, 0x0204));
					}
					NV_WR32(par->PGRAPH, 0x69F0,
						NV_RD32(par->PFB, 0x0200));
					NV_WR32(par->PGRAPH, 0x69F4,
						NV_RD32(par->PFB, 0x0204));

					NV_WR32(par->PGRAPH, 0x0840, 0);
					NV_WR32(par->PGRAPH, 0x0844, 0);
					NV_WR32(par->PGRAPH, 0x08a0,
						par->FbMapSize - 1);
					NV_WR32(par->PGRAPH, 0x08a4,
						par->FbMapSize - 1);
				}
			} else {
				NV_WR32(par->PGRAPH, 0x09A4,
					NV_RD32(par->PFB, 0x0200));
				NV_WR32(par->PGRAPH, 0x09A8,
					NV_RD32(par->PFB, 0x0204));
				NV_WR32(par->PGRAPH, 0x0750, 0x00EA0000);
				NV_WR32(par->PGRAPH, 0x0754,
					NV_RD32(par->PFB, 0x0200));
				NV_WR32(par->PGRAPH, 0x0750, 0x00EA0004);
				NV_WR32(par->PGRAPH, 0x0754,
					NV_RD32(par->PFB, 0x0204));

				NV_WR32(par->PGRAPH, 0x0820, 0);
				NV_WR32(par->PGRAPH, 0x0824, 0);
				NV_WR32(par->PGRAPH, 0x0864,
					par->FbMapSize - 1);
				NV_WR32(par->PGRAPH, 0x0868,
					par->FbMapSize - 1);
			}
			NV_WR32(par->PGRAPH, 0x0B20, 0x00000000);
			NV_WR32(par->PGRAPH, 0x0B04, 0xFFFFFFFF);
		}
	}
	NV_WR32(par->PGRAPH, 0x053C, 0);
	NV_WR32(par->PGRAPH, 0x0540, 0);
	NV_WR32(par->PGRAPH, 0x0544, 0x00007FFF);
	NV_WR32(par->PGRAPH, 0x0548, 0x00007FFF);

	NV_WR32(par->PFIFO, 0x0140 * 4, 0x00000000);
	NV_WR32(par->PFIFO, 0x0141 * 4, 0x00000001);
	NV_WR32(par->PFIFO, 0x0480 * 4, 0x00000000);
	NV_WR32(par->PFIFO, 0x0494 * 4, 0x00000000);
	if (par->Architecture >= NV_ARCH_40)
		NV_WR32(par->PFIFO, 0x0481 * 4, 0x00010000);
	else
		NV_WR32(par->PFIFO, 0x0481 * 4, 0x00000100);
	NV_WR32(par->PFIFO, 0x0490 * 4, 0x00000000);
	NV_WR32(par->PFIFO, 0x0491 * 4, 0x00000000);
	if (par->Architecture >= NV_ARCH_40)
		NV_WR32(par->PFIFO, 0x048B * 4, 0x00001213);
	else
		NV_WR32(par->PFIFO, 0x048B * 4, 0x00001209);
	NV_WR32(par->PFIFO, 0x0400 * 4, 0x00000000);
	NV_WR32(par->PFIFO, 0x0414 * 4, 0x00000000);
	NV_WR32(par->PFIFO, 0x0084 * 4, 0x03000100);
	NV_WR32(par->PFIFO, 0x0085 * 4, 0x00000110);
	NV_WR32(par->PFIFO, 0x0086 * 4, 0x00000112);
	NV_WR32(par->PFIFO, 0x0143 * 4, 0x0000FFFF);
	NV_WR32(par->PFIFO, 0x0496 * 4, 0x0000FFFF);
	NV_WR32(par->PFIFO, 0x0050 * 4, 0x00000000);
	NV_WR32(par->PFIFO, 0x0040 * 4, 0xFFFFFFFF);
	NV_WR32(par->PFIFO, 0x0415 * 4, 0x00000001);
	NV_WR32(par->PFIFO, 0x048C * 4, 0x00000000);
	NV_WR32(par->PFIFO, 0x04A0 * 4, 0x00000000);
#ifdef __BIG_ENDIAN
	NV_WR32(par->PFIFO, 0x0489 * 4, 0x800F0078);
#else
	NV_WR32(par->PFIFO, 0x0489 * 4, 0x000F0078);
#endif
	NV_WR32(par->PFIFO, 0x0488 * 4, 0x00000001);
	NV_WR32(par->PFIFO, 0x0480 * 4, 0x00000001);
	NV_WR32(par->PFIFO, 0x0494 * 4, 0x00000001);
	NV_WR32(par->PFIFO, 0x0495 * 4, 0x00000001);
	NV_WR32(par->PFIFO, 0x0140 * 4, 0x00000001);

    if (!state) {
	    par->CurrentState = NULL;
	    return;
    }

	if (par->Architecture >= NV_ARCH_10) {
		if (par->twoHeads) {
			NV_WR32(par->PCRTC0, 0x0860, state->head);
			NV_WR32(par->PCRTC0, 0x2860, state->head2);
		}
		NV_WR32(par->PRAMDAC, 0x0404, NV_RD32(par->PRAMDAC, 0x0404) |
			(1 << 25));

		NV_WR32(par->PMC, 0x8704, 1);
		NV_WR32(par->PMC, 0x8140, 0);
		NV_WR32(par->PMC, 0x8920, 0);
		NV_WR32(par->PMC, 0x8924, 0);
		NV_WR32(par->PMC, 0x8908, par->FbMapSize - 1);
		NV_WR32(par->PMC, 0x890C, par->FbMapSize - 1);
		NV_WR32(par->PMC, 0x1588, 0);

		NV_WR32(par->PCRTC, 0x0810, state->cursorConfig);
		NV_WR32(par->PCRTC, 0x0830, state->displayV - 3);
		NV_WR32(par->PCRTC, 0x0834, state->displayV - 1);

		if (par->FlatPanel) {
			if ((par->Chipset & 0x0ff0) == 0x0110) {
				NV_WR32(par->PRAMDAC, 0x0528, state->dither);
			} else if (par->twoHeads) {
				NV_WR32(par->PRAMDAC, 0x083C, state->dither);
			}

			VGA_WR08(par->PCIO, 0x03D4, 0x53);
			VGA_WR08(par->PCIO, 0x03D5, state->timingH);
			VGA_WR08(par->PCIO, 0x03D4, 0x54);
			VGA_WR08(par->PCIO, 0x03D5, state->timingV);
			VGA_WR08(par->PCIO, 0x03D4, 0x21);
			VGA_WR08(par->PCIO, 0x03D5, 0xfa);
		}

		VGA_WR08(par->PCIO, 0x03D4, 0x41);
		VGA_WR08(par->PCIO, 0x03D5, state->extra);
	}

	VGA_WR08(par->PCIO, 0x03D4, 0x19);
	VGA_WR08(par->PCIO, 0x03D5, state->repaint0);
	VGA_WR08(par->PCIO, 0x03D4, 0x1A);
	VGA_WR08(par->PCIO, 0x03D5, state->repaint1);
	VGA_WR08(par->PCIO, 0x03D4, 0x25);
	VGA_WR08(par->PCIO, 0x03D5, state->screen);
	VGA_WR08(par->PCIO, 0x03D4, 0x28);
	VGA_WR08(par->PCIO, 0x03D5, state->pixel);
	VGA_WR08(par->PCIO, 0x03D4, 0x2D);
	VGA_WR08(par->PCIO, 0x03D5, state->horiz);
	VGA_WR08(par->PCIO, 0x03D4, 0x1C);
	VGA_WR08(par->PCIO, 0x03D5, state->fifo);
	VGA_WR08(par->PCIO, 0x03D4, 0x1B);
	VGA_WR08(par->PCIO, 0x03D5, state->arbitration0);
	VGA_WR08(par->PCIO, 0x03D4, 0x20);
	VGA_WR08(par->PCIO, 0x03D5, state->arbitration1);

	if(par->Architecture >= NV_ARCH_30) {
		VGA_WR08(par->PCIO, 0x03D4, 0x47);
		VGA_WR08(par->PCIO, 0x03D5, state->arbitration1 >> 8);
	}

	VGA_WR08(par->PCIO, 0x03D4, 0x30);
	VGA_WR08(par->PCIO, 0x03D5, state->cursor0);
	VGA_WR08(par->PCIO, 0x03D4, 0x31);
	VGA_WR08(par->PCIO, 0x03D5, state->cursor1);
	VGA_WR08(par->PCIO, 0x03D4, 0x2F);
	VGA_WR08(par->PCIO, 0x03D5, state->cursor2);
	VGA_WR08(par->PCIO, 0x03D4, 0x39);
	VGA_WR08(par->PCIO, 0x03D5, state->interlace);

	if (!par->FlatPanel) {
		if (par->Architecture >= NV_ARCH_40)
			NV_WR32(par->PRAMDAC0, 0x0580, state->control);

		NV_WR32(par->PRAMDAC0, 0x050C, state->pllsel);
		NV_WR32(par->PRAMDAC0, 0x0508, state->vpll);
		if (par->twoHeads)
			NV_WR32(par->PRAMDAC0, 0x0520, state->vpll2);
		if (par->twoStagePLL) {
			NV_WR32(par->PRAMDAC0, 0x0578, state->vpllB);
			NV_WR32(par->PRAMDAC0, 0x057C, state->vpll2B);
		}
	} else {
		NV_WR32(par->PRAMDAC, 0x0848, state->scale);
		NV_WR32(par->PRAMDAC, 0x0828, state->crtcSync +
			par->PanelTweak);
	}

	NV_WR32(par->PRAMDAC, 0x0600, state->general);

	NV_WR32(par->PCRTC, 0x0140, 0);
	NV_WR32(par->PCRTC, 0x0100, 1);

	par->CurrentState = state;
}