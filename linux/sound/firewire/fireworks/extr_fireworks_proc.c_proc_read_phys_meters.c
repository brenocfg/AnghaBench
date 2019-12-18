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
typedef  int /*<<< orphan*/  u32 ;
struct snd_info_entry {struct snd_efw* private_data; } ;
struct snd_info_buffer {int dummy; } ;
struct snd_efw_phys_meters {int out_meters; int in_meters; int /*<<< orphan*/ * values; } ;
struct snd_efw {int phys_in; int phys_out; unsigned int phys_out_grp_count; unsigned int phys_in_grp_count; TYPE_1__* phys_in_grps; TYPE_1__* phys_out_grps; } ;
struct TYPE_2__ {unsigned int count; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 char* get_phys_name (TYPE_1__*,int) ; 
 int /*<<< orphan*/  kfree (struct snd_efw_phys_meters*) ; 
 struct snd_efw_phys_meters* kzalloc (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int min (int,int) ; 
 int snd_efw_command_get_phys_meters (struct snd_efw*,struct snd_efw_phys_meters*,unsigned int) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,...) ; 

__attribute__((used)) static void
proc_read_phys_meters(struct snd_info_entry *entry,
		      struct snd_info_buffer *buffer)
{
	struct snd_efw *efw = entry->private_data;
	struct snd_efw_phys_meters *meters;
	unsigned int g, c, m, max, size;
	const char *name;
	u32 *linear;
	int err;

	size = sizeof(struct snd_efw_phys_meters) +
	       (efw->phys_in + efw->phys_out) * sizeof(u32);
	meters = kzalloc(size, GFP_KERNEL);
	if (meters == NULL)
		return;

	err = snd_efw_command_get_phys_meters(efw, meters, size);
	if (err < 0)
		goto end;

	snd_iprintf(buffer, "Physical Meters:\n");

	m = 0;
	max = min(efw->phys_out, meters->out_meters);
	linear = meters->values;
	snd_iprintf(buffer, " %d Outputs:\n", max);
	for (g = 0; g < efw->phys_out_grp_count; g++) {
		name = get_phys_name(&efw->phys_out_grps[g], false);
		for (c = 0; c < efw->phys_out_grps[g].count; c++) {
			if (m < max)
				snd_iprintf(buffer, "\t%s [%d]: %d\n",
					    name, c, linear[m++]);
		}
	}

	m = 0;
	max = min(efw->phys_in, meters->in_meters);
	linear = meters->values + meters->out_meters;
	snd_iprintf(buffer, " %d Inputs:\n", max);
	for (g = 0; g < efw->phys_in_grp_count; g++) {
		name = get_phys_name(&efw->phys_in_grps[g], true);
		for (c = 0; c < efw->phys_in_grps[g].count; c++)
			if (m < max)
				snd_iprintf(buffer, "\t%s [%d]: %d\n",
					    name, c, linear[m++]);
	}
end:
	kfree(meters);
}