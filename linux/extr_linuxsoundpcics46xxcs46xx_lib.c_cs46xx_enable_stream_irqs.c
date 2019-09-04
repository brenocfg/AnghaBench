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
struct snd_cs46xx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BA0_HICR ; 
 int /*<<< orphan*/  BA1_CIE ; 
 int /*<<< orphan*/  BA1_PFIE ; 
 int HICR_CHGM ; 
 int HICR_IEV ; 
 unsigned int snd_cs46xx_peek (struct snd_cs46xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_cs46xx_poke (struct snd_cs46xx*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  snd_cs46xx_pokeBA0 (struct snd_cs46xx*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cs46xx_enable_stream_irqs(struct snd_cs46xx *chip)
{
	unsigned int tmp;

	snd_cs46xx_pokeBA0(chip, BA0_HICR, HICR_IEV | HICR_CHGM);
        
	tmp = snd_cs46xx_peek(chip, BA1_PFIE);
	tmp &= ~0x0000f03f;
	snd_cs46xx_poke(chip, BA1_PFIE, tmp);	/* playback interrupt enable */

	tmp = snd_cs46xx_peek(chip, BA1_CIE);
	tmp &= ~0x0000003f;
	tmp |=  0x00000001;
	snd_cs46xx_poke(chip, BA1_CIE, tmp);	/* capture interrupt enable */
}