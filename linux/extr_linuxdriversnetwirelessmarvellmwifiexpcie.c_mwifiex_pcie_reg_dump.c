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
typedef  int u32 ;
struct TYPE_2__ {struct mwifiex_pcie_card_reg* reg; } ;
struct pcie_service_card {TYPE_1__ pcie; } ;
struct mwifiex_pcie_card_reg {int fw_status; } ;
struct mwifiex_adapter {struct pcie_service_card* card; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  MSG ; 
 int PCIE_SCRATCH_12_REG ; 
 int PCIE_SCRATCH_14_REG ; 
 int PCIE_SCRATCH_15_REG ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ mwifiex_read_reg (struct mwifiex_adapter*,int,int*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static int
mwifiex_pcie_reg_dump(struct mwifiex_adapter *adapter, char *drv_buf)
{
	char *p = drv_buf;
	char buf[256], *ptr;
	int i;
	u32 value;
	struct pcie_service_card *card = adapter->card;
	const struct mwifiex_pcie_card_reg *reg = card->pcie.reg;
	int pcie_scratch_reg[] = {PCIE_SCRATCH_12_REG,
				  PCIE_SCRATCH_14_REG,
				  PCIE_SCRATCH_15_REG};

	if (!p)
		return 0;

	mwifiex_dbg(adapter, MSG, "PCIE register dump start\n");

	if (mwifiex_read_reg(adapter, reg->fw_status, &value)) {
		mwifiex_dbg(adapter, ERROR, "failed to read firmware status");
		return 0;
	}

	ptr = buf;
	mwifiex_dbg(adapter, MSG, "pcie scratch register:");
	for (i = 0; i < ARRAY_SIZE(pcie_scratch_reg); i++) {
		mwifiex_read_reg(adapter, pcie_scratch_reg[i], &value);
		ptr += sprintf(ptr, "reg:0x%x, value=0x%x\n",
			       pcie_scratch_reg[i], value);
	}

	mwifiex_dbg(adapter, MSG, "%s\n", buf);
	p += sprintf(p, "%s\n", buf);

	mwifiex_dbg(adapter, MSG, "PCIE register dump end\n");

	return p - drv_buf;
}