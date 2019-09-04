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
struct tb_ctl {int dummy; } ;
struct tb_cfg_result {int err; int tb_error; int /*<<< orphan*/  response_port; int /*<<< orphan*/  response_route; } ;

/* Variables and functions */
#define  TB_CFG_ERROR_INVALID_CONFIG_SPACE 131 
#define  TB_CFG_ERROR_LOOP 130 
#define  TB_CFG_ERROR_NO_SUCH_PORT 129 
#define  TB_CFG_ERROR_PORT_NOT_CONNECTED 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  tb_ctl_WARN (struct tb_ctl*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tb_cfg_print_error(struct tb_ctl *ctl,
			       const struct tb_cfg_result *res)
{
	WARN_ON(res->err != 1);
	switch (res->tb_error) {
	case TB_CFG_ERROR_PORT_NOT_CONNECTED:
		/* Port is not connected. This can happen during surprise
		 * removal. Do not warn. */
		return;
	case TB_CFG_ERROR_INVALID_CONFIG_SPACE:
		/*
		 * Invalid cfg_space/offset/length combination in
		 * cfg_read/cfg_write.
		 */
		tb_ctl_WARN(ctl,
			"CFG_ERROR(%llx:%x): Invalid config space or offset\n",
			res->response_route, res->response_port);
		return;
	case TB_CFG_ERROR_NO_SUCH_PORT:
		/*
		 * - The route contains a non-existent port.
		 * - The route contains a non-PHY port (e.g. PCIe).
		 * - The port in cfg_read/cfg_write does not exist.
		 */
		tb_ctl_WARN(ctl, "CFG_ERROR(%llx:%x): Invalid port\n",
			res->response_route, res->response_port);
		return;
	case TB_CFG_ERROR_LOOP:
		tb_ctl_WARN(ctl, "CFG_ERROR(%llx:%x): Route contains a loop\n",
			res->response_route, res->response_port);
		return;
	default:
		/* 5,6,7,9 and 11 are also valid error codes */
		tb_ctl_WARN(ctl, "CFG_ERROR(%llx:%x): Unknown error\n",
			res->response_route, res->response_port);
		return;
	}
}