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
struct snd_info_entry {struct snd_bebob* private_data; } ;
struct snd_info_buffer {int dummy; } ;
struct snd_bebob {int /*<<< orphan*/  unit; } ;
struct hw_info {char* protocol_ver; char* bld_ver; char* model_id; char* model_rev; char* fw_id; char* fw_ver; char* base_addr; char* max_size; int /*<<< orphan*/  bld_time; int /*<<< orphan*/  bld_date; int /*<<< orphan*/  fw_time; int /*<<< orphan*/  fw_date; int /*<<< orphan*/ * guid; int /*<<< orphan*/  manufacturer; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct hw_info*) ; 
 struct hw_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ snd_bebob_read_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hw_info*,int) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,char*,...) ; 

__attribute__((used)) static void
proc_read_hw_info(struct snd_info_entry *entry,
		  struct snd_info_buffer *buffer)
{
	struct snd_bebob *bebob = entry->private_data;
	struct hw_info *info;

	info = kzalloc(sizeof(struct hw_info), GFP_KERNEL);
	if (info == NULL)
		return;

	if (snd_bebob_read_block(bebob->unit, 0,
				   info, sizeof(struct hw_info)) < 0)
		goto end;

	snd_iprintf(buffer, "Manufacturer:\t%.8s\n",
		    (char *)&info->manufacturer);
	snd_iprintf(buffer, "Protocol Ver:\t%d\n", info->protocol_ver);
	snd_iprintf(buffer, "Build Ver:\t%d\n", info->bld_ver);
	snd_iprintf(buffer, "GUID:\t\t0x%.8X%.8X\n",
		    info->guid[0], info->guid[1]);
	snd_iprintf(buffer, "Model ID:\t0x%02X\n", info->model_id);
	snd_iprintf(buffer, "Model Rev:\t%d\n", info->model_rev);
	snd_iprintf(buffer, "Firmware Date:\t%.8s\n", (char *)&info->fw_date);
	snd_iprintf(buffer, "Firmware Time:\t%.8s\n", (char *)&info->fw_time);
	snd_iprintf(buffer, "Firmware ID:\t0x%X\n", info->fw_id);
	snd_iprintf(buffer, "Firmware Ver:\t%d\n", info->fw_ver);
	snd_iprintf(buffer, "Base Addr:\t0x%X\n", info->base_addr);
	snd_iprintf(buffer, "Max Size:\t%d\n", info->max_size);
	snd_iprintf(buffer, "Loader Date:\t%.8s\n", (char *)&info->bld_date);
	snd_iprintf(buffer, "Loader Time:\t%.8s\n", (char *)&info->bld_time);

end:
	kfree(info);
}