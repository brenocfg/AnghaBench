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
typedef  int /*<<< orphan*/  u8 ;
struct snd_msnd {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_msnd_dsp_full_reset (int /*<<< orphan*/ ) ; 
 int snd_msnd_send_dsp_cmd (struct snd_msnd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_msnd_send_dsp_cmd_chk(struct snd_msnd *chip, u8 cmd)
{
	if (snd_msnd_send_dsp_cmd(chip, cmd) == 0)
		return 0;
	snd_msnd_dsp_full_reset(chip->card);
	return snd_msnd_send_dsp_cmd(chip, cmd);
}