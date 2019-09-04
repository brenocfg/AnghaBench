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
struct xonar_cs43xx {int /*<<< orphan*/ * cs4398_regs; } ;
struct snd_info_buffer {int dummy; } ;
struct oxygen {struct xonar_cs43xx* model_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  dump_cs4362a_registers (struct xonar_cs43xx*,struct snd_info_buffer*) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,...) ; 

__attribute__((used)) static void dump_d1_registers(struct oxygen *chip,
			      struct snd_info_buffer *buffer)
{
	struct xonar_cs43xx *data = chip->model_data;
	unsigned int i;

	snd_iprintf(buffer, "\nCS4398: 7?");
	for (i = 2; i < 8; ++i)
		snd_iprintf(buffer, " %02x", data->cs4398_regs[i]);
	snd_iprintf(buffer, "\n");
	dump_cs4362a_registers(data, buffer);
}