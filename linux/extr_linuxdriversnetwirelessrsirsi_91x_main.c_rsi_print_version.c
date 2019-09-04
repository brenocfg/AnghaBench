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
struct TYPE_4__ {int /*<<< orphan*/  release_num; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;
struct rsi_common {TYPE_1__* priv; int /*<<< orphan*/  oper_mode; TYPE_2__ lmac_ver; } ;
struct TYPE_3__ {int /*<<< orphan*/  fw_file_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_ZONE ; 
 int /*<<< orphan*/  opmode_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsi_dbg (int /*<<< orphan*/ ,char*,...) ; 

void rsi_print_version(struct rsi_common *common)
{
	rsi_dbg(ERR_ZONE, "================================================\n");
	rsi_dbg(ERR_ZONE, "================ RSI Version Info ==============\n");
	rsi_dbg(ERR_ZONE, "================================================\n");
	rsi_dbg(ERR_ZONE, "FW Version\t: %d.%d.%d\n",
		common->lmac_ver.major, common->lmac_ver.minor,
		common->lmac_ver.release_num);
	rsi_dbg(ERR_ZONE, "Operating mode\t: %d [%s]",
		common->oper_mode, opmode_str(common->oper_mode));
	rsi_dbg(ERR_ZONE, "Firmware file\t: %s", common->priv->fw_file_name);
	rsi_dbg(ERR_ZONE, "================================================\n");
}