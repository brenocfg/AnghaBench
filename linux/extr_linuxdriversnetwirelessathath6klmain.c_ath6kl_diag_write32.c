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
typedef  int /*<<< orphan*/  u32 ;
struct ath6kl {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  ath6kl_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ath6kl_hif_diag_write32 (struct ath6kl*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ath6kl_diag_write32(struct ath6kl *ar, u32 address, __le32 value)
{
	int ret;

	ret = ath6kl_hif_diag_write32(ar, address, value);

	if (ret) {
		ath6kl_err("failed to write 0x%x during diagnose window to 0x%x\n",
			   address, value);
		return ret;
	}

	return 0;
}