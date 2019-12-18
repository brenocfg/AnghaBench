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
struct xonar_pcm179x {unsigned int dacs; int /*<<< orphan*/ ** pcm1796_regs; } ;
struct snd_info_buffer {int dummy; } ;
struct oxygen {struct xonar_pcm179x* model_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,...) ; 

__attribute__((used)) static void dump_pcm1796_registers(struct oxygen *chip,
				   struct snd_info_buffer *buffer)
{
	struct xonar_pcm179x *data = chip->model_data;
	unsigned int dac, i;

	for (dac = 0; dac < data->dacs; ++dac) {
		snd_iprintf(buffer, "\nPCM1796 %u:", dac + 1);
		for (i = 0; i < 5; ++i)
			snd_iprintf(buffer, " %02x",
				    data->pcm1796_regs[dac][i]);
	}
	snd_iprintf(buffer, "\n");
}