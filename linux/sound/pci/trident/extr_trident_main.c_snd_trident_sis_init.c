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
struct snd_trident {int /*<<< orphan*/  spdif_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  SI_SPDIF_CS ; 
 int /*<<< orphan*/  TRID_REG (struct snd_trident*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_trident_sis_reset (struct snd_trident*) ; 
 int /*<<< orphan*/  snd_trident_stop_all_voices (struct snd_trident*) ; 

__attribute__((used)) static int snd_trident_sis_init(struct snd_trident *trident)
{
	int err;

	if ((err = snd_trident_sis_reset(trident)) < 0)
		return err;

	snd_trident_stop_all_voices(trident);

	/* initialize S/PDIF */
	outl(trident->spdif_bits, TRID_REG(trident, SI_SPDIF_CS));

	return 0;
}