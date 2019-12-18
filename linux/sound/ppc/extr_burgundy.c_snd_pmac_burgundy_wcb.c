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
struct snd_pmac {TYPE_1__* awacs; } ;
struct TYPE_2__ {int /*<<< orphan*/  codec_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  out_le32 (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  snd_pmac_burgundy_busy_wait (struct snd_pmac*) ; 

__attribute__((used)) static void
snd_pmac_burgundy_wcb(struct snd_pmac *chip, unsigned int addr,
		      unsigned int val)
{
	out_le32(&chip->awacs->codec_ctrl, addr + 0x300000 + (val & 0xff));
	snd_pmac_burgundy_busy_wait(chip);
}