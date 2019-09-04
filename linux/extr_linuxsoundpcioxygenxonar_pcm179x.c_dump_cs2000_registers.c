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
struct xonar_pcm179x {int /*<<< orphan*/ * cs2000_regs; scalar_t__ has_cs2000; } ;
struct snd_info_buffer {int dummy; } ;
struct oxygen {struct xonar_pcm179x* model_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,...) ; 

__attribute__((used)) static void dump_cs2000_registers(struct oxygen *chip,
				  struct snd_info_buffer *buffer)
{
	struct xonar_pcm179x *data = chip->model_data;
	unsigned int i;

	if (data->has_cs2000) {
		snd_iprintf(buffer, "\nCS2000:\n00:   ");
		for (i = 1; i < 0x10; ++i)
			snd_iprintf(buffer, " %02x", data->cs2000_regs[i]);
		snd_iprintf(buffer, "\n10:");
		for (i = 0x10; i < 0x1f; ++i)
			snd_iprintf(buffer, " %02x", data->cs2000_regs[i]);
		snd_iprintf(buffer, "\n");
	}
}