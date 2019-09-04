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
typedef  int uint32_t ;
struct sk_buff {scalar_t__ data; } ;
struct htc_target {int /*<<< orphan*/  dev; } ;
struct htc_panic_bad_vaddr {int /*<<< orphan*/  badvaddr; int /*<<< orphan*/  pc; int /*<<< orphan*/  exccause; } ;
struct htc_panic_bad_epid {int /*<<< orphan*/  epid; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void ath9k_htc_fw_panic_report(struct htc_target *htc_handle,
				      struct sk_buff *skb)
{
	uint32_t *pattern = (uint32_t *)skb->data;

	switch (*pattern) {
	case 0x33221199:
		{
		struct htc_panic_bad_vaddr *htc_panic;
		htc_panic = (struct htc_panic_bad_vaddr *) skb->data;
		dev_err(htc_handle->dev, "ath: firmware panic! "
			"exccause: 0x%08x; pc: 0x%08x; badvaddr: 0x%08x.\n",
			htc_panic->exccause, htc_panic->pc,
			htc_panic->badvaddr);
		break;
		}
	case 0x33221299:
		{
		struct htc_panic_bad_epid *htc_panic;
		htc_panic = (struct htc_panic_bad_epid *) skb->data;
		dev_err(htc_handle->dev, "ath: firmware panic! "
			"bad epid: 0x%08x\n", htc_panic->epid);
		break;
		}
	default:
		dev_err(htc_handle->dev, "ath: unknown panic pattern!\n");
		break;
	}
}