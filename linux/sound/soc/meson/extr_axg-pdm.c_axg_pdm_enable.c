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
 int /*<<< orphan*/  PDM_CTRL ; 
 int /*<<< orphan*/  PDM_CTRL_EN ; 
 int /*<<< orphan*/  PDM_CTRL_RST_FIFO ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void axg_pdm_enable(struct regmap *map)
{
	/* Reset AFIFO */
	regmap_update_bits(map, PDM_CTRL, PDM_CTRL_RST_FIFO, PDM_CTRL_RST_FIFO);
	regmap_update_bits(map, PDM_CTRL, PDM_CTRL_RST_FIFO, 0);

	/* Enable PDM */
	regmap_update_bits(map, PDM_CTRL, PDM_CTRL_EN, PDM_CTRL_EN);
}