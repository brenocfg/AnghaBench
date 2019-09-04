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
struct meson_mx_efuse {int /*<<< orphan*/  core_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  MESON_MX_EFUSE_CNTL1 ; 
 int /*<<< orphan*/  MESON_MX_EFUSE_CNTL1_PD_ENABLE ; 
 int /*<<< orphan*/  MESON_MX_EFUSE_CNTL4 ; 
 int /*<<< orphan*/  MESON_MX_EFUSE_CNTL4_ENCRYPT_ENABLE ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  meson_mx_efuse_mask_bits (struct meson_mx_efuse*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int meson_mx_efuse_hw_enable(struct meson_mx_efuse *efuse)
{
	int err;

	err = clk_prepare_enable(efuse->core_clk);
	if (err)
		return err;

	/* power up the efuse */
	meson_mx_efuse_mask_bits(efuse, MESON_MX_EFUSE_CNTL1,
				 MESON_MX_EFUSE_CNTL1_PD_ENABLE, 0);

	meson_mx_efuse_mask_bits(efuse, MESON_MX_EFUSE_CNTL4,
				 MESON_MX_EFUSE_CNTL4_ENCRYPT_ENABLE, 0);

	return 0;
}