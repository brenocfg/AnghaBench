#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uuid_le ;
struct uuid_module {int id; int max_instance; int /*<<< orphan*/  is_loadable; int /*<<< orphan*/  uuid; int /*<<< orphan*/  list; int /*<<< orphan*/  instance_id; } ;
struct sst_dsp {int /*<<< orphan*/  dev; struct skl_sst* thread_context; } ;
struct skl_sst {int /*<<< orphan*/  uuid_list; } ;
struct firmware {char* data; unsigned int size; } ;
struct TYPE_4__ {int /*<<< orphan*/  load_type; } ;
struct TYPE_3__ {scalar_t__ id; } ;
struct adsp_module_entry {int instance_max_count; TYPE_2__ type; TYPE_1__ uuid; } ;
struct adsp_fw_hdr {int len; int num_modules; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct uuid_module* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skl_dsp_strip_extended_manifest (struct firmware*) ; 
 int /*<<< orphan*/  skl_freeup_uuid_list (struct skl_sst*) ; 

int snd_skl_parse_uuids(struct sst_dsp *ctx, const struct firmware *fw,
			unsigned int offset, int index)
{
	struct adsp_fw_hdr *adsp_hdr;
	struct adsp_module_entry *mod_entry;
	int i, num_entry, size;
	uuid_le *uuid_bin;
	const char *buf;
	struct skl_sst *skl = ctx->thread_context;
	struct uuid_module *module;
	struct firmware stripped_fw;
	unsigned int safe_file;
	int ret = 0;

	/* Get the FW pointer to derive ADSP header */
	stripped_fw.data = fw->data;
	stripped_fw.size = fw->size;

	skl_dsp_strip_extended_manifest(&stripped_fw);

	buf = stripped_fw.data;

	/* check if we have enough space in file to move to header */
	safe_file = sizeof(*adsp_hdr) + offset;
	if (stripped_fw.size <= safe_file) {
		dev_err(ctx->dev, "Small fw file size, No space for hdr\n");
		return -EINVAL;
	}

	adsp_hdr = (struct adsp_fw_hdr *)(buf + offset);

	/* check 1st module entry is in file */
	safe_file += adsp_hdr->len + sizeof(*mod_entry);
	if (stripped_fw.size <= safe_file) {
		dev_err(ctx->dev, "Small fw file size, No module entry\n");
		return -EINVAL;
	}

	mod_entry = (struct adsp_module_entry *)
		(buf + offset + adsp_hdr->len);

	num_entry = adsp_hdr->num_modules;

	/* check all entries are in file */
	safe_file += num_entry * sizeof(*mod_entry);
	if (stripped_fw.size <= safe_file) {
		dev_err(ctx->dev, "Small fw file size, No modules\n");
		return -EINVAL;
	}


	/*
	 * Read the UUID(GUID) from FW Manifest.
	 *
	 * The 16 byte UUID format is: XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXX
	 * Populate the UUID table to store module_id and loadable flags
	 * for the module.
	 */

	for (i = 0; i < num_entry; i++, mod_entry++) {
		module = kzalloc(sizeof(*module), GFP_KERNEL);
		if (!module) {
			ret = -ENOMEM;
			goto free_uuid_list;
		}

		uuid_bin = (uuid_le *)mod_entry->uuid.id;
		memcpy(&module->uuid, uuid_bin, sizeof(module->uuid));

		module->id = (i | (index << 12));
		module->is_loadable = mod_entry->type.load_type;
		module->max_instance = mod_entry->instance_max_count;
		size = sizeof(int) * mod_entry->instance_max_count;
		module->instance_id = devm_kzalloc(ctx->dev, size, GFP_KERNEL);
		if (!module->instance_id) {
			ret = -ENOMEM;
			goto free_uuid_list;
		}

		list_add_tail(&module->list, &skl->uuid_list);

		dev_dbg(ctx->dev,
			"Adding uuid :%pUL   mod id: %d  Loadable: %d\n",
			&module->uuid, module->id, module->is_loadable);
	}

	return 0;

free_uuid_list:
	skl_freeup_uuid_list(skl);
	return ret;
}