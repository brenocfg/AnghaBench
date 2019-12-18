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
struct snd_emu10k1_midi {int dummy; } ;
struct snd_emu10k1 {TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ mpu401_input_avail (struct snd_emu10k1*,struct snd_emu10k1_midi*) ; 
 int /*<<< orphan*/  mpu401_read_data (struct snd_emu10k1*,struct snd_emu10k1_midi*) ; 
 int /*<<< orphan*/  mpu401_read_stat (struct snd_emu10k1*,struct snd_emu10k1_midi*) ; 

__attribute__((used)) static void mpu401_clear_rx(struct snd_emu10k1 *emu, struct snd_emu10k1_midi *mpu)
{
	int timeout = 100000;
	for (; timeout > 0 && mpu401_input_avail(emu, mpu); timeout--)
		mpu401_read_data(emu, mpu);
#ifdef CONFIG_SND_DEBUG
	if (timeout <= 0)
		dev_err(emu->card->dev,
			"cmd: clear rx timeout (status = 0x%x)\n",
			mpu401_read_stat(emu, mpu));
#endif
}