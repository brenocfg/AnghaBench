#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* banks_16; TYPE_1__* banks_8; } ;
struct TYPE_8__ {int memory; int rom_memory; int rom_present; int /*<<< orphan*/  enh_mode; scalar_t__ rom_banks; TYPE_3__ mem_alloc; } ;
struct snd_gus_card {TYPE_4__ gf1; } ;
struct rom_hdr {int dummy; } ;
struct TYPE_6__ {unsigned int address; int size; } ;
struct TYPE_5__ {unsigned int address; int size; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (unsigned int*) ; 
 int /*<<< orphan*/  SNDRV_GF1_GB_GLOBAL_MODE ; 
 int /*<<< orphan*/  SNDRV_GF1_GB_MEMORY_CONTROL ; 
 int /*<<< orphan*/  SNDRV_GF1_GW_MEMORY_CONFIG ; 
 int snd_gf1_look16 (struct snd_gus_card*,int /*<<< orphan*/ ) ; 
 int snd_gf1_peek (struct snd_gus_card*,int) ; 
 int /*<<< orphan*/  snd_gf1_poke (struct snd_gus_card*,int,int) ; 
 int snd_gf1_read8 (struct snd_gus_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_gf1_write16 (struct snd_gus_card*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_gf1_write8 (struct snd_gus_card*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_interwave_bank_sizes (struct snd_gus_card*,int*) ; 
 int /*<<< orphan*/  snd_interwave_reset (struct snd_gus_card*) ; 
 scalar_t__ strncmp (unsigned char*,char*,int) ; 

__attribute__((used)) static void snd_interwave_detect_memory(struct snd_gus_card *gus)
{
	static unsigned int lmc[13] =
	{
		0x00000001, 0x00000101, 0x01010101, 0x00000401,
		0x04040401, 0x00040101, 0x04040101, 0x00000004,
		0x00000404, 0x04040404, 0x00000010, 0x00001010,
		0x10101010
	};

	int bank_pos, pages;
	unsigned int i, lmct;
	int psizes[4];
	unsigned char iwave[8];
	unsigned char csum;

	snd_interwave_reset(gus);
	snd_gf1_write8(gus, SNDRV_GF1_GB_GLOBAL_MODE, snd_gf1_read8(gus, SNDRV_GF1_GB_GLOBAL_MODE) | 0x01);		/* enhanced mode */
	snd_gf1_write8(gus, SNDRV_GF1_GB_MEMORY_CONTROL, 0x01);	/* DRAM I/O cycles selected */
	snd_gf1_write16(gus, SNDRV_GF1_GW_MEMORY_CONFIG, (snd_gf1_look16(gus, SNDRV_GF1_GW_MEMORY_CONFIG) & 0xff10) | 0x004c);
	/* ok.. simple test of memory size */
	pages = 0;
	snd_gf1_poke(gus, 0, 0x55);
	snd_gf1_poke(gus, 1, 0xaa);
#if 1
	if (snd_gf1_peek(gus, 0) == 0x55 && snd_gf1_peek(gus, 1) == 0xaa)
#else
	if (0)			/* ok.. for testing of 0k RAM */
#endif
	{
		snd_interwave_bank_sizes(gus, psizes);
		lmct = (psizes[3] << 24) | (psizes[2] << 16) |
		    (psizes[1] << 8) | psizes[0];
#if 0
		printk(KERN_DEBUG "lmct = 0x%08x\n", lmct);
#endif
		for (i = 0; i < ARRAY_SIZE(lmc); i++)
			if (lmct == lmc[i]) {
#if 0
				printk(KERN_DEBUG "found !!! %i\n", i);
#endif
				snd_gf1_write16(gus, SNDRV_GF1_GW_MEMORY_CONFIG, (snd_gf1_look16(gus, SNDRV_GF1_GW_MEMORY_CONFIG) & 0xfff0) | i);
				snd_interwave_bank_sizes(gus, psizes);
				break;
			}
		if (i >= ARRAY_SIZE(lmc) && !gus->gf1.enh_mode)
			 snd_gf1_write16(gus, SNDRV_GF1_GW_MEMORY_CONFIG, (snd_gf1_look16(gus, SNDRV_GF1_GW_MEMORY_CONFIG) & 0xfff0) | 2);
		for (i = 0; i < 4; i++) {
			gus->gf1.mem_alloc.banks_8[i].address =
			    gus->gf1.mem_alloc.banks_16[i].address = i << 22;
			gus->gf1.mem_alloc.banks_8[i].size =
			    gus->gf1.mem_alloc.banks_16[i].size = psizes[i] << 18;
			pages += psizes[i];
		}
	}
	pages <<= 18;
	gus->gf1.memory = pages;

	snd_gf1_write8(gus, SNDRV_GF1_GB_MEMORY_CONTROL, 0x03);	/* select ROM */
	snd_gf1_write16(gus, SNDRV_GF1_GW_MEMORY_CONFIG, (snd_gf1_look16(gus, SNDRV_GF1_GW_MEMORY_CONFIG) & 0xff1f) | (4 << 5));
	gus->gf1.rom_banks = 0;
	gus->gf1.rom_memory = 0;
	for (bank_pos = 0; bank_pos < 16L * 1024L * 1024L; bank_pos += 4L * 1024L * 1024L) {
		for (i = 0; i < 8; ++i)
			iwave[i] = snd_gf1_peek(gus, bank_pos + i);
		if (strncmp(iwave, "INTRWAVE", 8))
			continue;	/* first check */
		csum = 0;
		for (i = 0; i < sizeof(struct rom_hdr); i++)
			csum += snd_gf1_peek(gus, bank_pos + i);
		if (csum != 0)
			continue;	/* not valid rom */
		gus->gf1.rom_banks++;
		gus->gf1.rom_present |= 1 << (bank_pos >> 22);
		gus->gf1.rom_memory = snd_gf1_peek(gus, bank_pos + 40) |
				     (snd_gf1_peek(gus, bank_pos + 41) << 8) |
				     (snd_gf1_peek(gus, bank_pos + 42) << 16) |
				     (snd_gf1_peek(gus, bank_pos + 43) << 24);
	}
#if 0
	if (gus->gf1.rom_memory > 0) {
		if (gus->gf1.rom_banks == 1 && gus->gf1.rom_present == 8)
			gus->card->type = SNDRV_CARD_TYPE_IW_DYNASONIC;
	}
#endif
	snd_gf1_write8(gus, SNDRV_GF1_GB_MEMORY_CONTROL, 0x00);	/* select RAM */

	if (!gus->gf1.enh_mode)
		snd_interwave_reset(gus);
}