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
struct snd_mpu401 {int /*<<< orphan*/  private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDEX_MIDI_IN_STOP ; 
 int /*<<< orphan*/  snd_msnd_disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_msnd_send_dsp_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_msnd_mpu401_close(struct snd_mpu401 *mpu)
{
	snd_msnd_send_dsp_cmd(mpu->private_data, HDEX_MIDI_IN_STOP);
	snd_msnd_disable_irq(mpu->private_data);
}