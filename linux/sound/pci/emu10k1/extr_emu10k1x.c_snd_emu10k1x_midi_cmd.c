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
struct emu10k1x_midi {int /*<<< orphan*/  input_lock; } ;
struct emu10k1x {int /*<<< orphan*/  port; TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ MPU401_ACK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned char,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ mpu401_input_avail (struct emu10k1x*,struct emu10k1x_midi*) ; 
 scalar_t__ mpu401_read_data (struct emu10k1x*,struct emu10k1x_midi*) ; 
 int /*<<< orphan*/  mpu401_read_stat (struct emu10k1x*,struct emu10k1x_midi*) ; 
 int /*<<< orphan*/  mpu401_write_cmd (struct emu10k1x*,struct emu10k1x_midi*,unsigned char) ; 
 int /*<<< orphan*/  mpu401_write_data (struct emu10k1x*,struct emu10k1x_midi*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_emu10k1x_midi_cmd(struct emu10k1x * emu,
				  struct emu10k1x_midi *midi, unsigned char cmd, int ack)
{
	unsigned long flags;
	int timeout, ok;

	spin_lock_irqsave(&midi->input_lock, flags);
	mpu401_write_data(emu, midi, 0x00);
	/* mpu401_clear_rx(emu, midi); */

	mpu401_write_cmd(emu, midi, cmd);
	if (ack) {
		ok = 0;
		timeout = 10000;
		while (!ok && timeout-- > 0) {
			if (mpu401_input_avail(emu, midi)) {
				if (mpu401_read_data(emu, midi) == MPU401_ACK)
					ok = 1;
			}
		}
		if (!ok && mpu401_read_data(emu, midi) == MPU401_ACK)
			ok = 1;
	} else {
		ok = 1;
	}
	spin_unlock_irqrestore(&midi->input_lock, flags);
	if (!ok) {
		dev_err(emu->card->dev,
			"midi_cmd: 0x%x failed at 0x%lx (status = 0x%x, data = 0x%x)!!!\n",
			   cmd, emu->port,
			   mpu401_read_stat(emu, midi),
			   mpu401_read_data(emu, midi));
		return 1;
	}
	return 0;
}