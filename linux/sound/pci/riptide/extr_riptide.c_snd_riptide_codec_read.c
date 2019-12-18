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
union cmdret {unsigned short* retwords; } ;
struct snd_riptide {struct cmdif* cif; } ;
struct snd_ac97 {struct snd_riptide* private_data; } ;
struct cmdif {int dummy; } ;

/* Variables and functions */
 union cmdret CMDRET_ZERO ; 
 scalar_t__ SEND_RACR (struct cmdif*,unsigned short,union cmdret*) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_printdd (char*,unsigned short,unsigned short) ; 

__attribute__((used)) static unsigned short snd_riptide_codec_read(struct snd_ac97 *ac97,
					     unsigned short reg)
{
	struct snd_riptide *chip = ac97->private_data;
	struct cmdif *cif = chip->cif;
	union cmdret rptr = CMDRET_ZERO;

	if (snd_BUG_ON(!cif))
		return 0;

	if (SEND_RACR(cif, reg, &rptr) != 0)
		SEND_RACR(cif, reg, &rptr);
	snd_printdd("Read AC97 reg 0x%x got 0x%x\n", reg, rptr.retwords[1]);
	return rptr.retwords[1];
}