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
struct sdw_msg {int flags; scalar_t__ len; scalar_t__ page; } ;
struct sdw_cdns {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CDNS_MCP_CMD_READ ; 
 int CDNS_MCP_CMD_WRITE ; 
 int EINVAL ; 
#define  SDW_MSG_FLAG_READ 129 
#define  SDW_MSG_FLAG_WRITE 128 
 int cdns_program_scp_addr (struct sdw_cdns*,struct sdw_msg*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int cdns_prep_msg(struct sdw_cdns *cdns, struct sdw_msg *msg, int *cmd)
{
	int ret;

	if (msg->page) {
		ret = cdns_program_scp_addr(cdns, msg);
		if (ret) {
			msg->len = 0;
			return ret;
		}
	}

	switch (msg->flags) {
	case SDW_MSG_FLAG_READ:
		*cmd = CDNS_MCP_CMD_READ;
		break;

	case SDW_MSG_FLAG_WRITE:
		*cmd = CDNS_MCP_CMD_WRITE;
		break;

	default:
		dev_err(cdns->dev, "Invalid msg cmd: %d\n", msg->flags);
		return -EINVAL;
	}

	return 0;
}