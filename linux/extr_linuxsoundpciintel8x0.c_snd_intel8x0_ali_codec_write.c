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
struct snd_ac97 {scalar_t__ num; struct intel8x0* private_data; } ;
struct intel8x0 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALI_CPR ; 
 int /*<<< orphan*/  ALI_CPR_ADDR ; 
 unsigned short ALI_CPR_ADDR_SECONDARY ; 
 int /*<<< orphan*/  ALI_CSPSR_WRITE_OK ; 
 int /*<<< orphan*/  ICHREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iputword (struct intel8x0*,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  snd_intel8x0_ali_codec_ready (struct intel8x0*,int /*<<< orphan*/ ) ; 
 scalar_t__ snd_intel8x0_ali_codec_semaphore (struct intel8x0*) ; 

__attribute__((used)) static void snd_intel8x0_ali_codec_write(struct snd_ac97 *ac97, unsigned short reg,
					 unsigned short val)
{
	struct intel8x0 *chip = ac97->private_data;

	if (snd_intel8x0_ali_codec_semaphore(chip))
		return;
	iputword(chip, ICHREG(ALI_CPR), val);
	if (ac97->num)
		reg |= ALI_CPR_ADDR_SECONDARY;
	iputword(chip, ICHREG(ALI_CPR_ADDR), reg);
	snd_intel8x0_ali_codec_ready(chip, ALI_CSPSR_WRITE_OK);
}