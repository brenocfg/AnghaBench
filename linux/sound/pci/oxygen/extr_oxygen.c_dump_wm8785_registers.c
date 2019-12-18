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
struct snd_info_buffer {int dummy; } ;
struct oxygen {struct generic_data* model_data; } ;
struct generic_data {int /*<<< orphan*/ * wm8785_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,...) ; 

__attribute__((used)) static void dump_wm8785_registers(struct oxygen *chip,
				  struct snd_info_buffer *buffer)
{
	struct generic_data *data = chip->model_data;
	unsigned int i;

	snd_iprintf(buffer, "\nWM8785:");
	for (i = 0; i < 3; ++i)
		snd_iprintf(buffer, " %03x", data->wm8785_regs[i]);
	snd_iprintf(buffer, "\n");
}