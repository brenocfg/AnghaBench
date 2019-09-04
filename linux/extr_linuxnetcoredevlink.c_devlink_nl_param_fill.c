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
typedef  union devlink_param_value {int dummy; } devlink_param_value ;
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct devlink_param_item {union devlink_param_value driverinit_value; int /*<<< orphan*/  driverinit_value_valid; struct devlink_param* param; } ;
struct devlink_param_gset_ctx {int cmode; union devlink_param_value val; } ;
struct devlink_param {int /*<<< orphan*/  type; scalar_t__ generic; int /*<<< orphan*/  name; } ;
struct devlink {int dummy; } ;
typedef  enum devlink_command { ____Placeholder_devlink_command } devlink_command ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_ATTR_PARAM ; 
 int /*<<< orphan*/  DEVLINK_ATTR_PARAM_GENERIC ; 
 int /*<<< orphan*/  DEVLINK_ATTR_PARAM_NAME ; 
 int /*<<< orphan*/  DEVLINK_ATTR_PARAM_TYPE ; 
 int /*<<< orphan*/  DEVLINK_ATTR_PARAM_VALUES_LIST ; 
 int DEVLINK_PARAM_CMODE_DRIVERINIT ; 
 int DEVLINK_PARAM_CMODE_MAX ; 
 int EMSGSIZE ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  devlink_nl_family ; 
 int devlink_nl_param_value_fill_one (struct sk_buff*,int /*<<< orphan*/ ,int,union devlink_param_value) ; 
 scalar_t__ devlink_nl_put_handle (struct sk_buff*,struct devlink*) ; 
 int /*<<< orphan*/  devlink_param_cmode_is_supported (struct devlink_param const*,int) ; 
 int devlink_param_get (struct devlink*,struct devlink_param const*,struct devlink_param_gset_ctx*) ; 
 int devlink_param_type_to_nla_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genlmsg_cancel (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 void* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_flag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int devlink_nl_param_fill(struct sk_buff *msg, struct devlink *devlink,
				 struct devlink_param_item *param_item,
				 enum devlink_command cmd,
				 u32 portid, u32 seq, int flags)
{
	union devlink_param_value param_value[DEVLINK_PARAM_CMODE_MAX + 1];
	const struct devlink_param *param = param_item->param;
	struct devlink_param_gset_ctx ctx;
	struct nlattr *param_values_list;
	struct nlattr *param_attr;
	int nla_type;
	void *hdr;
	int err;
	int i;

	/* Get value from driver part to driverinit configuration mode */
	for (i = 0; i <= DEVLINK_PARAM_CMODE_MAX; i++) {
		if (!devlink_param_cmode_is_supported(param, i))
			continue;
		if (i == DEVLINK_PARAM_CMODE_DRIVERINIT) {
			if (!param_item->driverinit_value_valid)
				return -EOPNOTSUPP;
			param_value[i] = param_item->driverinit_value;
		} else {
			ctx.cmode = i;
			err = devlink_param_get(devlink, param, &ctx);
			if (err)
				return err;
			param_value[i] = ctx.val;
		}
	}

	hdr = genlmsg_put(msg, portid, seq, &devlink_nl_family, flags, cmd);
	if (!hdr)
		return -EMSGSIZE;

	if (devlink_nl_put_handle(msg, devlink))
		goto genlmsg_cancel;
	param_attr = nla_nest_start(msg, DEVLINK_ATTR_PARAM);
	if (!param_attr)
		goto genlmsg_cancel;
	if (nla_put_string(msg, DEVLINK_ATTR_PARAM_NAME, param->name))
		goto param_nest_cancel;
	if (param->generic && nla_put_flag(msg, DEVLINK_ATTR_PARAM_GENERIC))
		goto param_nest_cancel;

	nla_type = devlink_param_type_to_nla_type(param->type);
	if (nla_type < 0)
		goto param_nest_cancel;
	if (nla_put_u8(msg, DEVLINK_ATTR_PARAM_TYPE, nla_type))
		goto param_nest_cancel;

	param_values_list = nla_nest_start(msg, DEVLINK_ATTR_PARAM_VALUES_LIST);
	if (!param_values_list)
		goto param_nest_cancel;

	for (i = 0; i <= DEVLINK_PARAM_CMODE_MAX; i++) {
		if (!devlink_param_cmode_is_supported(param, i))
			continue;
		err = devlink_nl_param_value_fill_one(msg, param->type,
						      i, param_value[i]);
		if (err)
			goto values_list_nest_cancel;
	}

	nla_nest_end(msg, param_values_list);
	nla_nest_end(msg, param_attr);
	genlmsg_end(msg, hdr);
	return 0;

values_list_nest_cancel:
	nla_nest_end(msg, param_values_list);
param_nest_cancel:
	nla_nest_cancel(msg, param_attr);
genlmsg_cancel:
	genlmsg_cancel(msg, hdr);
	return -EMSGSIZE;
}