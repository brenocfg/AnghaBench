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
typedef  size_t u32 ;
struct sk_buff {int dummy; } ;
struct hwsim_new_radio_params {int channels; int no_vif; char const* hwname; int use_chanctx; void* perm_addr; int /*<<< orphan*/  regd; void* reg_alpha2; scalar_t__ destroy_on_close; scalar_t__ p2p_device; scalar_t__ reg_strict; int /*<<< orphan*/  member_0; } ;
struct genl_info {scalar_t__* attrs; int /*<<< orphan*/  extack; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int CFG80211_MAX_NUM_DIFFERENT_CHANNELS ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GENL_SET_ERR_MSG (struct genl_info*,char*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t HWSIM_ATTR_CHANNELS ; 
 size_t HWSIM_ATTR_DESTROY_RADIO_ON_CLOSE ; 
 size_t HWSIM_ATTR_NO_VIF ; 
 size_t HWSIM_ATTR_PERM_ADDR ; 
 size_t HWSIM_ATTR_RADIO_NAME ; 
 size_t HWSIM_ATTR_REG_CUSTOM_REG ; 
 size_t HWSIM_ATTR_REG_HINT_ALPHA2 ; 
 size_t HWSIM_ATTR_REG_STRICT_REG ; 
 size_t HWSIM_ATTR_SUPPORT_P2P_DEVICE ; 
 size_t HWSIM_ATTR_USE_CHANCTX ; 
 int /*<<< orphan*/  NL_SET_BAD_ATTR (int /*<<< orphan*/ ,scalar_t__) ; 
 size_t array_index_nospec (size_t,size_t) ; 
 int channels ; 
 int /*<<< orphan*/ * hwsim_world_regdom_custom ; 
 int /*<<< orphan*/  is_valid_ether_addr (void*) ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kfree (char const*) ; 
 int mac80211_hwsim_new_radio (struct genl_info*,struct hwsim_new_radio_params*) ; 
 void* nla_data (scalar_t__) ; 
 void* nla_get_u32 (scalar_t__) ; 
 int /*<<< orphan*/  nla_len (scalar_t__) ; 

__attribute__((used)) static int hwsim_new_radio_nl(struct sk_buff *msg, struct genl_info *info)
{
	struct hwsim_new_radio_params param = { 0 };
	const char *hwname = NULL;
	int ret;

	param.reg_strict = info->attrs[HWSIM_ATTR_REG_STRICT_REG];
	param.p2p_device = info->attrs[HWSIM_ATTR_SUPPORT_P2P_DEVICE];
	param.channels = channels;
	param.destroy_on_close =
		info->attrs[HWSIM_ATTR_DESTROY_RADIO_ON_CLOSE];

	if (info->attrs[HWSIM_ATTR_CHANNELS])
		param.channels = nla_get_u32(info->attrs[HWSIM_ATTR_CHANNELS]);

	if (param.channels < 1) {
		GENL_SET_ERR_MSG(info, "must have at least one channel");
		return -EINVAL;
	}

	if (param.channels > CFG80211_MAX_NUM_DIFFERENT_CHANNELS) {
		GENL_SET_ERR_MSG(info, "too many channels specified");
		return -EINVAL;
	}

	if (info->attrs[HWSIM_ATTR_NO_VIF])
		param.no_vif = true;

	if (info->attrs[HWSIM_ATTR_RADIO_NAME]) {
		hwname = kasprintf(GFP_KERNEL, "%.*s",
				   nla_len(info->attrs[HWSIM_ATTR_RADIO_NAME]),
				   (char *)nla_data(info->attrs[HWSIM_ATTR_RADIO_NAME]));
		if (!hwname)
			return -ENOMEM;
		param.hwname = hwname;
	}

	if (info->attrs[HWSIM_ATTR_USE_CHANCTX])
		param.use_chanctx = true;
	else
		param.use_chanctx = (param.channels > 1);

	if (info->attrs[HWSIM_ATTR_REG_HINT_ALPHA2])
		param.reg_alpha2 =
			nla_data(info->attrs[HWSIM_ATTR_REG_HINT_ALPHA2]);

	if (info->attrs[HWSIM_ATTR_REG_CUSTOM_REG]) {
		u32 idx = nla_get_u32(info->attrs[HWSIM_ATTR_REG_CUSTOM_REG]);

		if (idx >= ARRAY_SIZE(hwsim_world_regdom_custom)) {
			kfree(hwname);
			return -EINVAL;
		}

		idx = array_index_nospec(idx,
					 ARRAY_SIZE(hwsim_world_regdom_custom));
		param.regd = hwsim_world_regdom_custom[idx];
	}

	if (info->attrs[HWSIM_ATTR_PERM_ADDR]) {
		if (!is_valid_ether_addr(
				nla_data(info->attrs[HWSIM_ATTR_PERM_ADDR]))) {
			GENL_SET_ERR_MSG(info,"MAC is no valid source addr");
			NL_SET_BAD_ATTR(info->extack,
					info->attrs[HWSIM_ATTR_PERM_ADDR]);
			kfree(hwname);
			return -EINVAL;
		}


		param.perm_addr = nla_data(info->attrs[HWSIM_ATTR_PERM_ADDR]);
	}

	ret = mac80211_hwsim_new_radio(info, &param);
	kfree(hwname);
	return ret;
}