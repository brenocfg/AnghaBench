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
struct regmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PDM_F1_CTRL ; 
 int /*<<< orphan*/  PDM_F2_CTRL ; 
 int /*<<< orphan*/  PDM_F3_CTRL ; 
 unsigned int PDM_FILTER_EN ; 
 int /*<<< orphan*/  PDM_HCIC_CTRL1 ; 
 int /*<<< orphan*/  PDM_HPF_CTRL ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static void axg_pdm_filters_enable(struct regmap *map, bool enable)
{
	unsigned int val = enable ? PDM_FILTER_EN : 0;

	regmap_update_bits(map, PDM_HCIC_CTRL1, PDM_FILTER_EN, val);
	regmap_update_bits(map, PDM_F1_CTRL, PDM_FILTER_EN, val);
	regmap_update_bits(map, PDM_F2_CTRL, PDM_FILTER_EN, val);
	regmap_update_bits(map, PDM_F3_CTRL, PDM_FILTER_EN, val);
	regmap_update_bits(map, PDM_HPF_CTRL, PDM_FILTER_EN, val);
}