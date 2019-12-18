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
struct TYPE_2__ {int /*<<< orphan*/  s; int /*<<< orphan*/  i; } ;
struct switch_val {scalar_t__ err; TYPE_1__ value; } ;
struct nl_msg {int dummy; } ;
struct genlmsghdr {int dummy; } ;

/* Variables and functions */
 int NL_SKIP ; 
 scalar_t__ SWITCH_ATTR_MAX ; 
 size_t SWITCH_ATTR_OP_VALUE_INT ; 
 size_t SWITCH_ATTR_OP_VALUE_LINK ; 
 size_t SWITCH_ATTR_OP_VALUE_PORTS ; 
 size_t SWITCH_ATTR_OP_VALUE_STR ; 
 int /*<<< orphan*/  genlmsg_attrdata (struct genlmsghdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genlmsg_attrlen (struct genlmsghdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_get_string (scalar_t__) ; 
 int /*<<< orphan*/  nla_get_u32 (scalar_t__) ; 
 scalar_t__ nla_parse (scalar_t__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct genlmsghdr* nlmsg_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_hdr (struct nl_msg*) ; 
 scalar_t__ store_link_val (struct nl_msg*,scalar_t__,struct switch_val*) ; 
 scalar_t__ store_port_val (struct nl_msg*,scalar_t__,struct switch_val*) ; 
 int /*<<< orphan*/  strdup (int /*<<< orphan*/ ) ; 
 scalar_t__* tb ; 

__attribute__((used)) static int
store_val(struct nl_msg *msg, void *arg)
{
	struct genlmsghdr *gnlh = nlmsg_data(nlmsg_hdr(msg));
	struct switch_val *val = arg;

	if (!val)
		goto error;

	if (nla_parse(tb, SWITCH_ATTR_MAX - 1, genlmsg_attrdata(gnlh, 0),
			genlmsg_attrlen(gnlh, 0), NULL) < 0) {
		goto error;
	}

	if (tb[SWITCH_ATTR_OP_VALUE_INT])
		val->value.i = nla_get_u32(tb[SWITCH_ATTR_OP_VALUE_INT]);
	else if (tb[SWITCH_ATTR_OP_VALUE_STR])
		val->value.s = strdup(nla_get_string(tb[SWITCH_ATTR_OP_VALUE_STR]));
	else if (tb[SWITCH_ATTR_OP_VALUE_PORTS])
		val->err = store_port_val(msg, tb[SWITCH_ATTR_OP_VALUE_PORTS], val);
	else if (tb[SWITCH_ATTR_OP_VALUE_LINK])
		val->err = store_link_val(msg, tb[SWITCH_ATTR_OP_VALUE_LINK], val);

	val->err = 0;
	return 0;

error:
	return NL_SKIP;
}