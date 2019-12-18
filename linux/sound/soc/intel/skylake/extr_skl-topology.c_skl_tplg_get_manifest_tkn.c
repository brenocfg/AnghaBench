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
typedef  int /*<<< orphan*/  u8 ;
struct snd_soc_tplg_vendor_value_elem {int dummy; } ;
struct snd_soc_tplg_vendor_string_elem {int dummy; } ;
struct snd_soc_tplg_vendor_array {int type; int num_elems; struct snd_soc_tplg_vendor_value_elem* value; TYPE_2__* uuid; scalar_t__ size; } ;
struct skl_dev {TYPE_1__** modules; int /*<<< orphan*/  nr_modules; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  guid_t ;
struct TYPE_4__ {int /*<<< orphan*/  uuid; int /*<<< orphan*/  token; } ;
struct TYPE_3__ {int /*<<< orphan*/  uuid; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SKL_TKN_UUID ; 
#define  SND_SOC_TPLG_TUPLE_TYPE_STRING 129 
#define  SND_SOC_TPLG_TUPLE_TYPE_UUID 128 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  guid_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int skl_tplg_get_int_tkn (struct device*,struct snd_soc_tplg_vendor_value_elem*,struct skl_dev*) ; 
 int skl_tplg_get_str_tkn (struct device*,struct snd_soc_tplg_vendor_array*,struct skl_dev*) ; 

__attribute__((used)) static int skl_tplg_get_manifest_tkn(struct device *dev,
		char *pvt_data, struct skl_dev *skl,
		int block_size)
{
	int tkn_count = 0, ret;
	int off = 0, tuple_size = 0;
	u8 uuid_index = 0;
	struct snd_soc_tplg_vendor_array *array;
	struct snd_soc_tplg_vendor_value_elem *tkn_elem;

	if (block_size <= 0)
		return -EINVAL;

	while (tuple_size < block_size) {
		array = (struct snd_soc_tplg_vendor_array *)(pvt_data + off);
		off += array->size;
		switch (array->type) {
		case SND_SOC_TPLG_TUPLE_TYPE_STRING:
			ret = skl_tplg_get_str_tkn(dev, array, skl);

			if (ret < 0)
				return ret;
			tkn_count = ret;

			tuple_size += tkn_count *
				sizeof(struct snd_soc_tplg_vendor_string_elem);
			continue;

		case SND_SOC_TPLG_TUPLE_TYPE_UUID:
			if (array->uuid->token != SKL_TKN_UUID) {
				dev_err(dev, "Not an UUID token: %d\n",
					array->uuid->token);
				return -EINVAL;
			}
			if (uuid_index >= skl->nr_modules) {
				dev_err(dev, "Too many UUID tokens\n");
				return -EINVAL;
			}
			guid_copy(&skl->modules[uuid_index++]->uuid,
				  (guid_t *)&array->uuid->uuid);

			tuple_size += sizeof(*array->uuid);
			continue;

		default:
			tkn_elem = array->value;
			tkn_count = 0;
			break;
		}

		while (tkn_count <= array->num_elems - 1) {
			ret = skl_tplg_get_int_tkn(dev,
					tkn_elem, skl);
			if (ret < 0)
				return ret;

			tkn_count = tkn_count + ret;
			tkn_elem++;
		}
		tuple_size += (tkn_count * sizeof(*tkn_elem));
		tkn_count = 0;
	}

	return off;
}