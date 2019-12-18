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
struct snd_ali {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALI_REG (struct snd_ali*,scalar_t__) ; 
 scalar_t__ ALI_SPDIF_CS ; 
 scalar_t__ ALI_SPDIF_CTRL ; 
 unsigned char inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outw (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_ali_set_spdif_out_rate(struct snd_ali *codec, unsigned int rate)
{
	unsigned char  bVal;
	unsigned int  dwRate;
	
	switch (rate) {
	case 32000: dwRate = 0x300; break;
	case 48000: dwRate = 0x200; break;
	default: dwRate = 0; break;
	}
	
	bVal  = inb(ALI_REG(codec, ALI_SPDIF_CTRL));
	bVal &= (unsigned char)(~(1<<6));
	
	bVal |= 0x80;		/* select right */
	outb(bVal, ALI_REG(codec, ALI_SPDIF_CTRL));
	outb(dwRate | 0x20, ALI_REG(codec, ALI_SPDIF_CS + 2));
	
	bVal &= ~0x80;	/* select left */
	outb(bVal, ALI_REG(codec, ALI_SPDIF_CTRL));
	outw(rate | 0x10, ALI_REG(codec, ALI_SPDIF_CS + 2));
}