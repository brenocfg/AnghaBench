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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct ath6kl {TYPE_1__* wiphy; int /*<<< orphan*/  target_type; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_2__ {int /*<<< orphan*/  fw_version; int /*<<< orphan*/  hw_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_IRQ ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  HI_ITEM (int /*<<< orphan*/ ) ; 
 int REGISTER_DUMP_COUNT ; 
 int REGISTER_DUMP_LEN_MAX ; 
 int TARG_VTOP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int ath6kl_diag_read (struct ath6kl*,int,int /*<<< orphan*/ *,int) ; 
 int ath6kl_diag_read32 (struct ath6kl*,int,int*) ; 
 int ath6kl_get_hi_item_addr (struct ath6kl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath6kl_info (char*,...) ; 
 int /*<<< orphan*/  ath6kl_warn (char*,int) ; 
 int /*<<< orphan*/  hi_failure_state ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath6kl_hif_dump_fw_crash(struct ath6kl *ar)
{
	__le32 regdump_val[REGISTER_DUMP_LEN_MAX];
	u32 i, address, regdump_addr = 0;
	int ret;

	/* the reg dump pointer is copied to the host interest area */
	address = ath6kl_get_hi_item_addr(ar, HI_ITEM(hi_failure_state));
	address = TARG_VTOP(ar->target_type, address);

	/* read RAM location through diagnostic window */
	ret = ath6kl_diag_read32(ar, address, &regdump_addr);

	if (ret || !regdump_addr) {
		ath6kl_warn("failed to get ptr to register dump area: %d\n",
			    ret);
		return;
	}

	ath6kl_dbg(ATH6KL_DBG_IRQ, "register dump data address 0x%x\n",
		   regdump_addr);
	regdump_addr = TARG_VTOP(ar->target_type, regdump_addr);

	/* fetch register dump data */
	ret = ath6kl_diag_read(ar, regdump_addr, (u8 *)&regdump_val[0],
				  REGISTER_DUMP_COUNT * (sizeof(u32)));
	if (ret) {
		ath6kl_warn("failed to get register dump: %d\n", ret);
		return;
	}

	ath6kl_info("crash dump:\n");
	ath6kl_info("hw 0x%x fw %s\n", ar->wiphy->hw_version,
		    ar->wiphy->fw_version);

	BUILD_BUG_ON(REGISTER_DUMP_COUNT % 4);

	for (i = 0; i < REGISTER_DUMP_COUNT; i += 4) {
		ath6kl_info("%d: 0x%8.8x 0x%8.8x 0x%8.8x 0x%8.8x\n",
			    i,
			    le32_to_cpu(regdump_val[i]),
			    le32_to_cpu(regdump_val[i + 1]),
			    le32_to_cpu(regdump_val[i + 2]),
			    le32_to_cpu(regdump_val[i + 3]));
	}
}