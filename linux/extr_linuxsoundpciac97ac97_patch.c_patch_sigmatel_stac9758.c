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
struct snd_ac97 {int subsystem_vendor; int subsystem_device; int /*<<< orphan*/  flags; int /*<<< orphan*/ * build_ops; scalar_t__ pci; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_INT_PAGING ; 
 int /*<<< orphan*/  AC97_PAGE_MASK ; 
 int /*<<< orphan*/  AC97_PAGE_VENDOR ; 
#define  AC97_SIGMATEL_INSEL 131 
#define  AC97_SIGMATEL_IOMISC 130 
#define  AC97_SIGMATEL_OUTSEL 129 
#define  AC97_SIGMATEL_VARIOUS 128 
 int /*<<< orphan*/  AC97_STEREO_MUTES ; 
 int /*<<< orphan*/  patch_sigmatel_stac9758_ops ; 
 int /*<<< orphan*/  snd_ac97_update_bits (struct snd_ac97*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ac97_write_cache (struct snd_ac97*,unsigned short,unsigned short) ; 

__attribute__((used)) static int patch_sigmatel_stac9758(struct snd_ac97 * ac97)
{
	static unsigned short regs[4] = {
		AC97_SIGMATEL_OUTSEL,
		AC97_SIGMATEL_IOMISC,
		AC97_SIGMATEL_INSEL,
		AC97_SIGMATEL_VARIOUS
	};
	static unsigned short def_regs[4] = {
		/* OUTSEL */ 0xd794, /* CL:CL, SR:SR, LO:MX, LI:DS, MI:DS */
		/* IOMISC */ 0x2001,
		/* INSEL */ 0x0201, /* LI:LI, MI:M1 */
		/* VARIOUS */ 0x0040
	};
	static unsigned short m675_regs[4] = {
		/* OUTSEL */ 0xfc70, /* CL:MX, SR:MX, LO:DS, LI:MX, MI:DS */
		/* IOMISC */ 0x2102, /* HP amp on */
		/* INSEL */ 0x0203, /* LI:LI, MI:FR */
		/* VARIOUS */ 0x0041 /* stereo mic */
	};
	unsigned short *pregs = def_regs;
	int i;

	/* Gateway M675 notebook */
	if (ac97->pci && 
	    ac97->subsystem_vendor == 0x107b &&
	    ac97->subsystem_device == 0x0601)
	    	pregs = m675_regs;

	// patch for SigmaTel
	ac97->build_ops = &patch_sigmatel_stac9758_ops;
	/* FIXME: assume only page 0 for writing cache */
	snd_ac97_update_bits(ac97, AC97_INT_PAGING, AC97_PAGE_MASK, AC97_PAGE_VENDOR);
	for (i = 0; i < 4; i++)
		snd_ac97_write_cache(ac97, regs[i], pregs[i]);

	ac97->flags |= AC97_STEREO_MUTES;
	return 0;
}