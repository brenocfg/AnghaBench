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
struct snd_ac97 {int dummy; } ;
struct TYPE_2__ {int flag; scalar_t__ value; scalar_t__ def; } ;

/* Variables and functions */
 int /*<<< orphan*/  CODEC_FAKE ; 
 int LM4550_REG_DONEREAD ; 
 int LM4550_REG_FAKEPROBE ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 TYPE_1__* lm4550_regfile ; 
 int /*<<< orphan*/  snd_ac97_write (struct snd_ac97*,int,scalar_t__) ; 

__attribute__((used)) static void lm4550_regfile_write_values_after_init(struct snd_ac97 *ac97)
{
	int i;
	for (i = 0; i < 64; i++)
		if ((lm4550_regfile[i].flag & LM4550_REG_FAKEPROBE) &&
		    (lm4550_regfile[i].value != lm4550_regfile[i].def)) {
			PDEBUG(CODEC_FAKE, "lm4550_regfile_write_values_after_"
			       "init(): reg=0x%x value=0x%x / %d is different "
			       "from def=0x%x / %d\n",
			       i, lm4550_regfile[i].value,
			       lm4550_regfile[i].value, lm4550_regfile[i].def,
			       lm4550_regfile[i].def);
			snd_ac97_write(ac97, i * 2, lm4550_regfile[i].value);
			lm4550_regfile[i].flag |= LM4550_REG_DONEREAD;
		}
}