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
struct snd_ca_midi {scalar_t__ ack; int /*<<< orphan*/  dev_id; int /*<<< orphan*/  (* get_dev_id_port ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  input_lock; } ;

/* Variables and functions */
 scalar_t__ ca_midi_input_avail (struct snd_ca_midi*) ; 
 scalar_t__ ca_midi_read_data (struct snd_ca_midi*) ; 
 int /*<<< orphan*/  ca_midi_read_stat (struct snd_ca_midi*) ; 
 int /*<<< orphan*/  ca_midi_write_cmd (struct snd_ca_midi*,unsigned char) ; 
 int /*<<< orphan*/  ca_midi_write_data (struct snd_ca_midi*,int) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned char,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ca_midi_cmd(struct snd_ca_midi *midi, unsigned char cmd, int ack)
{
	unsigned long flags;
	int timeout, ok;

	spin_lock_irqsave(&midi->input_lock, flags);
	ca_midi_write_data(midi, 0x00);
	/* ca_midi_clear_rx(midi); */

	ca_midi_write_cmd(midi, cmd);
	if (ack) {
		ok = 0;
		timeout = 10000;
		while (!ok && timeout-- > 0) {
			if (ca_midi_input_avail(midi)) {
				if (ca_midi_read_data(midi) == midi->ack)
					ok = 1;
			}
		}
		if (!ok && ca_midi_read_data(midi) == midi->ack)
			ok = 1;
	} else {
		ok = 1;
	}
	spin_unlock_irqrestore(&midi->input_lock, flags);
	if (!ok)
		pr_err("ca_midi_cmd: 0x%x failed at 0x%x (status = 0x%x, data = 0x%x)!!!\n",
			   cmd,
			   midi->get_dev_id_port(midi->dev_id),
			   ca_midi_read_stat(midi),
			   ca_midi_read_data(midi));
}