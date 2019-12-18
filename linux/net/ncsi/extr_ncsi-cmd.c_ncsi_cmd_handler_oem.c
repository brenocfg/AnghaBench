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
struct sk_buff {int dummy; } ;
struct ncsi_cmd_pkt_hdr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  common; } ;
struct ncsi_cmd_oem_pkt {TYPE_1__ cmd; int /*<<< orphan*/  mfr_id; } ;
struct ncsi_cmd_arg {int payload; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  ncsi_cmd_build_header (int /*<<< orphan*/ *,struct ncsi_cmd_arg*) ; 
 struct ncsi_cmd_oem_pkt* skb_put_zero (struct sk_buff*,unsigned int) ; 

__attribute__((used)) static int ncsi_cmd_handler_oem(struct sk_buff *skb,
				struct ncsi_cmd_arg *nca)
{
	struct ncsi_cmd_oem_pkt *cmd;
	unsigned int len;

	len = sizeof(struct ncsi_cmd_pkt_hdr) + 4;
	if (nca->payload < 26)
		len += 26;
	else
		len += nca->payload;

	cmd = skb_put_zero(skb, len);
	memcpy(&cmd->mfr_id, nca->data, nca->payload);
	ncsi_cmd_build_header(&cmd->cmd.common, nca);

	return 0;
}