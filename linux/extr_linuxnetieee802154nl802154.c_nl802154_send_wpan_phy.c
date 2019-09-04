#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct TYPE_4__ {scalar_t__ mode; scalar_t__ opt; } ;
struct TYPE_6__ {int flags; int /*<<< orphan*/  cca_ed_level; int /*<<< orphan*/  transmit_power; TYPE_1__ cca; int /*<<< orphan*/  current_channel; int /*<<< orphan*/  current_page; } ;
struct cfg802154_registered_device {scalar_t__ wpan_phy_idx; TYPE_2__* ops; TYPE_3__ wpan_phy; } ;
typedef  enum nl802154_commands { ____Placeholder_nl802154_commands } nl802154_commands ;
struct TYPE_5__ {scalar_t__ set_cca_mode; scalar_t__ set_cca_ed_level; scalar_t__ set_tx_power; scalar_t__ set_ackreq_default; scalar_t__ set_lbt_mode; scalar_t__ set_max_frame_retries; scalar_t__ set_max_csma_backoffs; scalar_t__ set_backoff_exponent; scalar_t__ set_short_addr; scalar_t__ set_pan_id; scalar_t__ set_channel; scalar_t__ del_virtual_intf; scalar_t__ add_virtual_intf; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  NL802154_ATTR_CCA_ED_LEVEL ; 
 int NL802154_ATTR_CCA_MODE ; 
 int NL802154_ATTR_CCA_OPT ; 
 int /*<<< orphan*/  NL802154_ATTR_CHANNEL ; 
 int NL802154_ATTR_GENERATION ; 
 int /*<<< orphan*/  NL802154_ATTR_PAGE ; 
 int /*<<< orphan*/  NL802154_ATTR_SUPPORTED_COMMANDS ; 
 int /*<<< orphan*/  NL802154_ATTR_TX_POWER ; 
 int NL802154_ATTR_WPAN_PHY ; 
 int /*<<< orphan*/  NL802154_ATTR_WPAN_PHY_NAME ; 
 scalar_t__ NL802154_CCA_ENERGY_CARRIER ; 
 scalar_t__ NL802154_CMD_DEL_INTERFACE ; 
 scalar_t__ NL802154_CMD_NEW_INTERFACE ; 
 int NL802154_CMD_NEW_WPAN_PHY ; 
 scalar_t__ NL802154_CMD_SET_ACKREQ_DEFAULT ; 
 scalar_t__ NL802154_CMD_SET_BACKOFF_EXPONENT ; 
 scalar_t__ NL802154_CMD_SET_CCA_ED_LEVEL ; 
 scalar_t__ NL802154_CMD_SET_CCA_MODE ; 
 scalar_t__ NL802154_CMD_SET_CHANNEL ; 
 scalar_t__ NL802154_CMD_SET_LBT_MODE ; 
 scalar_t__ NL802154_CMD_SET_MAX_CSMA_BACKOFFS ; 
 scalar_t__ NL802154_CMD_SET_MAX_FRAME_RETRIES ; 
 scalar_t__ NL802154_CMD_SET_PAN_ID ; 
 scalar_t__ NL802154_CMD_SET_SHORT_ADDR ; 
 scalar_t__ NL802154_CMD_SET_TX_POWER ; 
 int WPAN_PHY_FLAG_CCA_ED_LEVEL ; 
 int WPAN_PHY_FLAG_CCA_MODE ; 
 int WPAN_PHY_FLAG_TXPOWER ; 
 scalar_t__ cfg802154_rdev_list_generation ; 
 int /*<<< orphan*/  genlmsg_cancel (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 scalar_t__ nl802154_put_capabilities (struct sk_buff*,struct cfg802154_registered_device*) ; 
 scalar_t__ nl802154_send_wpan_phy_channels (struct cfg802154_registered_device*,struct sk_buff*) ; 
 void* nl802154hdr_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_s32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int,scalar_t__) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpan_phy_name (TYPE_3__*) ; 

__attribute__((used)) static int nl802154_send_wpan_phy(struct cfg802154_registered_device *rdev,
				  enum nl802154_commands cmd,
				  struct sk_buff *msg, u32 portid, u32 seq,
				  int flags)
{
	struct nlattr *nl_cmds;
	void *hdr;
	int i;

	hdr = nl802154hdr_put(msg, portid, seq, flags, cmd);
	if (!hdr)
		return -ENOBUFS;

	if (nla_put_u32(msg, NL802154_ATTR_WPAN_PHY, rdev->wpan_phy_idx) ||
	    nla_put_string(msg, NL802154_ATTR_WPAN_PHY_NAME,
			   wpan_phy_name(&rdev->wpan_phy)) ||
	    nla_put_u32(msg, NL802154_ATTR_GENERATION,
			cfg802154_rdev_list_generation))
		goto nla_put_failure;

	if (cmd != NL802154_CMD_NEW_WPAN_PHY)
		goto finish;

	/* DUMP PHY PIB */

	/* current channel settings */
	if (nla_put_u8(msg, NL802154_ATTR_PAGE,
		       rdev->wpan_phy.current_page) ||
	    nla_put_u8(msg, NL802154_ATTR_CHANNEL,
		       rdev->wpan_phy.current_channel))
		goto nla_put_failure;

	/* TODO remove this behaviour, we still keep support it for a while
	 * so users can change the behaviour to the new one.
	 */
	if (nl802154_send_wpan_phy_channels(rdev, msg))
		goto nla_put_failure;

	/* cca mode */
	if (rdev->wpan_phy.flags & WPAN_PHY_FLAG_CCA_MODE) {
		if (nla_put_u32(msg, NL802154_ATTR_CCA_MODE,
				rdev->wpan_phy.cca.mode))
			goto nla_put_failure;

		if (rdev->wpan_phy.cca.mode == NL802154_CCA_ENERGY_CARRIER) {
			if (nla_put_u32(msg, NL802154_ATTR_CCA_OPT,
					rdev->wpan_phy.cca.opt))
				goto nla_put_failure;
		}
	}

	if (rdev->wpan_phy.flags & WPAN_PHY_FLAG_TXPOWER) {
		if (nla_put_s32(msg, NL802154_ATTR_TX_POWER,
				rdev->wpan_phy.transmit_power))
			goto nla_put_failure;
	}

	if (rdev->wpan_phy.flags & WPAN_PHY_FLAG_CCA_ED_LEVEL) {
		if (nla_put_s32(msg, NL802154_ATTR_CCA_ED_LEVEL,
				rdev->wpan_phy.cca_ed_level))
			goto nla_put_failure;
	}

	if (nl802154_put_capabilities(msg, rdev))
		goto nla_put_failure;

	nl_cmds = nla_nest_start(msg, NL802154_ATTR_SUPPORTED_COMMANDS);
	if (!nl_cmds)
		goto nla_put_failure;

	i = 0;
#define CMD(op, n)							\
	do {								\
		if (rdev->ops->op) {					\
			i++;						\
			if (nla_put_u32(msg, i, NL802154_CMD_ ## n))	\
				goto nla_put_failure;			\
		}							\
	} while (0)

	CMD(add_virtual_intf, NEW_INTERFACE);
	CMD(del_virtual_intf, DEL_INTERFACE);
	CMD(set_channel, SET_CHANNEL);
	CMD(set_pan_id, SET_PAN_ID);
	CMD(set_short_addr, SET_SHORT_ADDR);
	CMD(set_backoff_exponent, SET_BACKOFF_EXPONENT);
	CMD(set_max_csma_backoffs, SET_MAX_CSMA_BACKOFFS);
	CMD(set_max_frame_retries, SET_MAX_FRAME_RETRIES);
	CMD(set_lbt_mode, SET_LBT_MODE);
	CMD(set_ackreq_default, SET_ACKREQ_DEFAULT);

	if (rdev->wpan_phy.flags & WPAN_PHY_FLAG_TXPOWER)
		CMD(set_tx_power, SET_TX_POWER);

	if (rdev->wpan_phy.flags & WPAN_PHY_FLAG_CCA_ED_LEVEL)
		CMD(set_cca_ed_level, SET_CCA_ED_LEVEL);

	if (rdev->wpan_phy.flags & WPAN_PHY_FLAG_CCA_MODE)
		CMD(set_cca_mode, SET_CCA_MODE);

#undef CMD
	nla_nest_end(msg, nl_cmds);

finish:
	genlmsg_end(msg, hdr);
	return 0;

nla_put_failure:
	genlmsg_cancel(msg, hdr);
	return -EMSGSIZE;
}