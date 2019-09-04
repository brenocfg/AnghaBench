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
struct mvebu_mpp_ctrl_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPP_GENERAL_CONFIG ; 
 int /*<<< orphan*/  NAND_GPIO_EN ; 
 int /*<<< orphan*/  gconfmap ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dove_nand_ctrl_set(struct mvebu_mpp_ctrl_data *data, unsigned pid,
			      unsigned long config)
{
	regmap_update_bits(gconfmap, MPP_GENERAL_CONFIG,
			   NAND_GPIO_EN,
			   (config) ? NAND_GPIO_EN : 0);
	return 0;
}