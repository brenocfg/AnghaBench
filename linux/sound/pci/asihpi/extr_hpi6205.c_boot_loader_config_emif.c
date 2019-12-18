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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct hpi_adapter_obj {int dummy; } ;

/* Variables and functions */
 int C6713_EMIF_CE0 ; 
 int C6713_EMIF_GCTL ; 
 int C6713_EMIF_SDRAMCTL ; 
 int C6713_EMIF_SDRAMEXT ; 
 int C6713_EMIF_SDRAMTIMING ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HPI6205_ERROR_C6713_HPIA ; 
 int /*<<< orphan*/  HPI6205_ERROR_C6713_HPIC ; 
 int /*<<< orphan*/  HPI6205_ERROR_C6713_PLL ; 
 int /*<<< orphan*/  HPI6205_ERROR_DSP_EMIF1 ; 
 int /*<<< orphan*/  HPI6205_ERROR_DSP_EMIF2 ; 
 int /*<<< orphan*/  HPI6205_ERROR_DSP_EMIF3 ; 
 int /*<<< orphan*/  HPI6205_ERROR_DSP_EMIF4 ; 
 int HPIAH_ADDR ; 
 int HPIAL_ADDR ; 
 int HPICH_ADDR ; 
 int HPICL_ADDR ; 
 int /*<<< orphan*/  HPI_DEBUG_LOG (int /*<<< orphan*/ ,char*,int,int) ; 
 long MTYPE_OFS ; 
 long RH_OFS ; 
 long RST_OFS ; 
 long RS_OFS ; 
 long WH_OFS ; 
 long WST_OFS ; 
 long WS_OFS ; 
 int boot_loader_read_mem32 (struct hpi_adapter_obj*,int,int) ; 
 int /*<<< orphan*/  boot_loader_write_mem32 (struct hpi_adapter_obj*,int,int,int) ; 
 int /*<<< orphan*/  hpios_delay_micro_seconds (int) ; 

__attribute__((used)) static u16 boot_loader_config_emif(struct hpi_adapter_obj *pao, int dsp_index)
{
	if (dsp_index == 0) {
		u32 setting;

		/* DSP 0 is always C6205 */

		/* Set the EMIF */
		/* memory map of C6205 */
		/* 00000000-0000FFFF    16Kx32 internal program */
		/* 00400000-00BFFFFF    CE0     2Mx32 SDRAM running @ 100MHz */

		/* EMIF config */
		/*------------ */
		/* Global EMIF control */
		boot_loader_write_mem32(pao, dsp_index, 0x01800000, 0x3779);
#define WS_OFS 28
#define WST_OFS 22
#define WH_OFS 20
#define RS_OFS 16
#define RST_OFS 8
#define MTYPE_OFS 4
#define RH_OFS 0

		/* EMIF CE0 setup - 2Mx32 Sync DRAM on ASI5000 cards only */
		setting = 0x00000030;
		boot_loader_write_mem32(pao, dsp_index, 0x01800008, setting);
		if (setting != boot_loader_read_mem32(pao, dsp_index,
				0x01800008))
			return HPI6205_ERROR_DSP_EMIF1;

		/* EMIF CE1 setup - 32 bit async. This is 6713 #1 HPI, */
		/* which occupies D15..0. 6713 starts at 27MHz, so need */
		/* plenty of wait states. See dsn8701.rtf, and 6713 errata. */
		/* WST should be 71, but 63  is max possible */
		setting =
			(1L << WS_OFS) | (63L << WST_OFS) | (1L << WH_OFS) |
			(1L << RS_OFS) | (63L << RST_OFS) | (1L << RH_OFS) |
			(2L << MTYPE_OFS);
		boot_loader_write_mem32(pao, dsp_index, 0x01800004, setting);
		if (setting != boot_loader_read_mem32(pao, dsp_index,
				0x01800004))
			return HPI6205_ERROR_DSP_EMIF2;

		/* EMIF CE2 setup - 32 bit async. This is 6713 #2 HPI, */
		/* which occupies D15..0. 6713 starts at 27MHz, so need */
		/* plenty of wait states */
		setting =
			(1L << WS_OFS) | (28L << WST_OFS) | (1L << WH_OFS) |
			(1L << RS_OFS) | (63L << RST_OFS) | (1L << RH_OFS) |
			(2L << MTYPE_OFS);
		boot_loader_write_mem32(pao, dsp_index, 0x01800010, setting);
		if (setting != boot_loader_read_mem32(pao, dsp_index,
				0x01800010))
			return HPI6205_ERROR_DSP_EMIF3;

		/* EMIF CE3 setup - 32 bit async. */
		/* This is the PLD on the ASI5000 cards only */
		setting =
			(1L << WS_OFS) | (10L << WST_OFS) | (1L << WH_OFS) |
			(1L << RS_OFS) | (10L << RST_OFS) | (1L << RH_OFS) |
			(2L << MTYPE_OFS);
		boot_loader_write_mem32(pao, dsp_index, 0x01800014, setting);
		if (setting != boot_loader_read_mem32(pao, dsp_index,
				0x01800014))
			return HPI6205_ERROR_DSP_EMIF4;

		/* set EMIF SDRAM control for 2Mx32 SDRAM (512x32x4 bank) */
		/*  need to use this else DSP code crashes? */
		boot_loader_write_mem32(pao, dsp_index, 0x01800018,
			0x07117000);

		/* EMIF SDRAM Refresh Timing */
		/* EMIF SDRAM timing  (orig = 0x410, emulator = 0x61a) */
		boot_loader_write_mem32(pao, dsp_index, 0x0180001C,
			0x00000410);

	} else if (dsp_index == 1) {
		/* test access to the C6713s HPI registers */
		u32 write_data = 0, read_data = 0, i = 0;

		/* Set up HPIC for little endian, by setiing HPIC:HWOB=1 */
		write_data = 1;
		boot_loader_write_mem32(pao, 0, HPICL_ADDR, write_data);
		boot_loader_write_mem32(pao, 0, HPICH_ADDR, write_data);
		/* C67 HPI is on lower 16bits of 32bit EMIF */
		read_data =
			0xFFF7 & boot_loader_read_mem32(pao, 0, HPICL_ADDR);
		if (write_data != read_data) {
			HPI_DEBUG_LOG(ERROR, "HPICL %x %x\n", write_data,
				read_data);
			return HPI6205_ERROR_C6713_HPIC;
		}
		/* HPIA - walking ones test */
		write_data = 1;
		for (i = 0; i < 32; i++) {
			boot_loader_write_mem32(pao, 0, HPIAL_ADDR,
				write_data);
			boot_loader_write_mem32(pao, 0, HPIAH_ADDR,
				(write_data >> 16));
			read_data =
				0xFFFF & boot_loader_read_mem32(pao, 0,
				HPIAL_ADDR);
			read_data =
				read_data | ((0xFFFF &
					boot_loader_read_mem32(pao, 0,
						HPIAH_ADDR))
				<< 16);
			if (read_data != write_data) {
				HPI_DEBUG_LOG(ERROR, "HPIA %x %x\n",
					write_data, read_data);
				return HPI6205_ERROR_C6713_HPIA;
			}
			write_data = write_data << 1;
		}

		/* setup C67x PLL
		 *  ** C6713 datasheet says we cannot program PLL from HPI,
		 * and indeed if we try to set the PLL multiply from the HPI,
		 * the PLL does not seem to lock, so we enable the PLL and
		 * use the default multiply of x 7, which for a 27MHz clock
		 * gives a DSP speed of 189MHz
		 */
		/* bypass PLL */
		boot_loader_write_mem32(pao, dsp_index, 0x01B7C100, 0x0000);
		hpios_delay_micro_seconds(1000);
		/* EMIF = 189/3=63MHz */
		boot_loader_write_mem32(pao, dsp_index, 0x01B7C120, 0x8002);
		/* peri = 189/2 */
		boot_loader_write_mem32(pao, dsp_index, 0x01B7C11C, 0x8001);
		/* cpu  = 189/1 */
		boot_loader_write_mem32(pao, dsp_index, 0x01B7C118, 0x8000);
		hpios_delay_micro_seconds(1000);
		/* ** SGT test to take GPO3 high when we start the PLL */
		/* and low when the delay is completed */
		/* FSX0 <- '1' (GPO3) */
		boot_loader_write_mem32(pao, 0, (0x018C0024L), 0x00002A0A);
		/* PLL not bypassed */
		boot_loader_write_mem32(pao, dsp_index, 0x01B7C100, 0x0001);
		hpios_delay_micro_seconds(1000);
		/* FSX0 <- '0' (GPO3) */
		boot_loader_write_mem32(pao, 0, (0x018C0024L), 0x00002A02);

		/* 6205 EMIF CE1 resetup - 32 bit async. */
		/* Now 6713 #1 is running at 189MHz can reduce waitstates */
		boot_loader_write_mem32(pao, 0, 0x01800004,	/* CE1 */
			(1L << WS_OFS) | (8L << WST_OFS) | (1L << WH_OFS) |
			(1L << RS_OFS) | (12L << RST_OFS) | (1L << RH_OFS) |
			(2L << MTYPE_OFS));

		hpios_delay_micro_seconds(1000);

		/* check that we can read one of the PLL registers */
		/* PLL should not be bypassed! */
		if ((boot_loader_read_mem32(pao, dsp_index, 0x01B7C100) & 0xF)
			!= 0x0001) {
			return HPI6205_ERROR_C6713_PLL;
		}
		/* setup C67x EMIF  (note this is the only use of
		   BAR1 via BootLoader_WriteMem32) */
		boot_loader_write_mem32(pao, dsp_index, C6713_EMIF_GCTL,
			0x000034A8);

		/* EMIF CE0 setup - 2Mx32 Sync DRAM
		   31..28       Wr setup
		   27..22       Wr strobe
		   21..20       Wr hold
		   19..16       Rd setup
		   15..14       -
		   13..8        Rd strobe
		   7..4         MTYPE   0011            Sync DRAM 32bits
		   3            Wr hold MSB
		   2..0         Rd hold
		 */
		boot_loader_write_mem32(pao, dsp_index, C6713_EMIF_CE0,
			0x00000030);

		/* EMIF SDRAM Extension
		   0x00
		   31-21        0000b 0000b 000b
		   20           WR2RD = 2cycles-1  = 1b

		   19-18        WR2DEAC = 3cycle-1 = 10b
		   17           WR2WR = 2cycle-1   = 1b
		   16-15        R2WDQM = 4cycle-1  = 11b
		   14-12        RD2WR = 6cycles-1  = 101b

		   11-10        RD2DEAC = 4cycle-1 = 11b
		   9            RD2RD = 2cycle-1   = 1b
		   8-7          THZP = 3cycle-1    = 10b
		   6-5          TWR  = 2cycle-1    = 01b (tWR = 17ns)
		   4            TRRD = 2cycle      = 0b  (tRRD = 14ns)
		   3-1          TRAS = 5cycle-1    = 100b (Tras=42ns)
		   1            CAS latency = 3cyc = 1b
		   (for Micron 2M32-7 operating at 100MHz)
		 */
		boot_loader_write_mem32(pao, dsp_index, C6713_EMIF_SDRAMEXT,
			0x001BDF29);

		/* EMIF SDRAM control - set up for a 2Mx32 SDRAM (512x32x4 bank)
		   31           -       0b       -
		   30           SDBSZ   1b              4 bank
		   29..28       SDRSZ   00b             11 row address pins

		   27..26       SDCSZ   01b             8 column address pins
		   25           RFEN    1b              refersh enabled
		   24           INIT    1b              init SDRAM!

		   23..20       TRCD    0001b                   (Trcd/Tcyc)-1 = (20/10)-1 = 1

		   19..16       TRP     0001b                   (Trp/Tcyc)-1 = (20/10)-1 = 1

		   15..12       TRC     0110b                   (Trc/Tcyc)-1 = (70/10)-1 = 6

		   11..0        -       0000b 0000b 0000b
		 */
		boot_loader_write_mem32(pao, dsp_index, C6713_EMIF_SDRAMCTL,
			0x47116000);

		/* SDRAM refresh timing
		   Need 4,096 refresh cycles every 64ms = 15.625us = 1562cycles of 100MHz = 0x61A
		 */
		boot_loader_write_mem32(pao, dsp_index,
			C6713_EMIF_SDRAMTIMING, 0x00000410);

		hpios_delay_micro_seconds(1000);
	} else if (dsp_index == 2) {
		/* DSP 2 is a C6713 */
	}

	return 0;
}