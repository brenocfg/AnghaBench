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
struct snd_cs46xx {struct dsp_spos_instance* dsp_spos_instance; } ;
struct dsp_spos_instance {struct dsp_scb_descriptor* the_null_scb; } ;
struct dsp_scb_descriptor {struct dsp_scb_descriptor* next_scb_ptr; } ;

/* Variables and functions */
 scalar_t__ snd_BUG_ON (int) ; 

__attribute__((used)) static struct dsp_scb_descriptor *
find_next_free_scb (struct snd_cs46xx * chip, struct dsp_scb_descriptor * from)
{
	struct dsp_spos_instance * ins = chip->dsp_spos_instance;
	struct dsp_scb_descriptor * scb = from;

	while (scb->next_scb_ptr != ins->the_null_scb) {
		if (snd_BUG_ON(!scb->next_scb_ptr))
			return NULL;

		scb = scb->next_scb_ptr;
	}

	return scb;
}