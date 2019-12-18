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
struct oxygen {struct dg* model_data; } ;
struct dg {int /*<<< orphan*/ * cs4245_shadow; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CS4245_INT_STATUS ; 
 int /*<<< orphan*/  cs4245_read_spi (struct oxygen*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,...) ; 

void dump_cs4245_registers(struct oxygen *chip,
				  struct snd_info_buffer *buffer)
{
	struct dg *data = chip->model_data;
	unsigned int addr;

	snd_iprintf(buffer, "\nCS4245:");
	cs4245_read_spi(chip, CS4245_INT_STATUS);
	for (addr = 1; addr < ARRAY_SIZE(data->cs4245_shadow); addr++)
		snd_iprintf(buffer, " %02x", data->cs4245_shadow[addr]);
	snd_iprintf(buffer, "\n");
}