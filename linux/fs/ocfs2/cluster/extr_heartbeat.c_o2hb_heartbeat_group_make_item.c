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
struct config_item {int dummy; } ;
struct o2hb_region {scalar_t__ hr_region_num; int /*<<< orphan*/  hr_handler_list; struct config_item hr_item; int /*<<< orphan*/  hr_key; int /*<<< orphan*/  hr_all_item; } ;
struct o2hb_nego_msg {int dummy; } ;
struct config_group {int dummy; } ;

/* Variables and functions */
 int EFBIG ; 
 int ENAMETOOLONG ; 
 int ENOMEM ; 
 struct config_item* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ O2HB_MAX_REGION_NAME_LEN ; 
 int /*<<< orphan*/  O2HB_NEGO_APPROVE_MSG ; 
 int /*<<< orphan*/  O2HB_NEGO_TIMEOUT_MSG ; 
 scalar_t__ O2NM_MAX_REGIONS ; 
 int /*<<< orphan*/  config_item_init_type_name (struct config_item*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crc32_le (scalar_t__,char const*,scalar_t__) ; 
 scalar_t__ find_first_zero_bit (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct o2hb_region*) ; 
 struct o2hb_region* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  o2hb_all_regions ; 
 int /*<<< orphan*/  o2hb_debug_dir ; 
 int /*<<< orphan*/  o2hb_debug_region_init (struct o2hb_region*,int /*<<< orphan*/ ) ; 
 scalar_t__ o2hb_global_heartbeat_active () ; 
 int /*<<< orphan*/  o2hb_live_lock ; 
 int /*<<< orphan*/  o2hb_nego_approve_handler ; 
 int /*<<< orphan*/  o2hb_nego_timeout_handler ; 
 int /*<<< orphan*/  o2hb_region_bitmap ; 
 int /*<<< orphan*/  o2hb_region_type ; 
 int o2net_register_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct o2hb_region*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  o2net_unregister_handler_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static struct config_item *o2hb_heartbeat_group_make_item(struct config_group *group,
							  const char *name)
{
	struct o2hb_region *reg = NULL;
	int ret;

	reg = kzalloc(sizeof(struct o2hb_region), GFP_KERNEL);
	if (reg == NULL)
		return ERR_PTR(-ENOMEM);

	if (strlen(name) > O2HB_MAX_REGION_NAME_LEN) {
		ret = -ENAMETOOLONG;
		goto free;
	}

	spin_lock(&o2hb_live_lock);
	reg->hr_region_num = 0;
	if (o2hb_global_heartbeat_active()) {
		reg->hr_region_num = find_first_zero_bit(o2hb_region_bitmap,
							 O2NM_MAX_REGIONS);
		if (reg->hr_region_num >= O2NM_MAX_REGIONS) {
			spin_unlock(&o2hb_live_lock);
			ret = -EFBIG;
			goto free;
		}
		set_bit(reg->hr_region_num, o2hb_region_bitmap);
	}
	list_add_tail(&reg->hr_all_item, &o2hb_all_regions);
	spin_unlock(&o2hb_live_lock);

	config_item_init_type_name(&reg->hr_item, name, &o2hb_region_type);

	/* this is the same way to generate msg key as dlm, for local heartbeat,
	 * name is also the same, so make initial crc value different to avoid
	 * message key conflict.
	 */
	reg->hr_key = crc32_le(reg->hr_region_num + O2NM_MAX_REGIONS,
		name, strlen(name));
	INIT_LIST_HEAD(&reg->hr_handler_list);
	ret = o2net_register_handler(O2HB_NEGO_TIMEOUT_MSG, reg->hr_key,
			sizeof(struct o2hb_nego_msg),
			o2hb_nego_timeout_handler,
			reg, NULL, &reg->hr_handler_list);
	if (ret)
		goto free;

	ret = o2net_register_handler(O2HB_NEGO_APPROVE_MSG, reg->hr_key,
			sizeof(struct o2hb_nego_msg),
			o2hb_nego_approve_handler,
			reg, NULL, &reg->hr_handler_list);
	if (ret)
		goto unregister_handler;

	o2hb_debug_region_init(reg, o2hb_debug_dir);

	return &reg->hr_item;

unregister_handler:
	o2net_unregister_handler_list(&reg->hr_handler_list);
free:
	kfree(reg);
	return ERR_PTR(ret);
}