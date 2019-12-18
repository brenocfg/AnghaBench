#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct intel8x0 {TYPE_1__* card; int /*<<< orphan*/  in_ac97_init; scalar_t__ buggy_semaphore; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALI_CAS ; 
 int ALI_CAS_SEM_BUSY ; 
 int /*<<< orphan*/  ALI_CSPSR_CODEC_READY ; 
 int /*<<< orphan*/  ICHREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int igetdword (struct intel8x0*,int /*<<< orphan*/ ) ; 
 int snd_intel8x0_ali_codec_ready (struct intel8x0*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int snd_intel8x0_ali_codec_semaphore(struct intel8x0 *chip)
{
	int time = 100;
	if (chip->buggy_semaphore)
		return 0; /* just ignore ... */
	while (--time && (igetdword(chip, ICHREG(ALI_CAS)) & ALI_CAS_SEM_BUSY))
		udelay(1);
	if (! time && ! chip->in_ac97_init)
		dev_warn(chip->card->dev, "ali_codec_semaphore timeout\n");
	return snd_intel8x0_ali_codec_ready(chip, ALI_CSPSR_CODEC_READY);
}