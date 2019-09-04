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
struct nau8825 {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAU8825_IMM_EN ; 
 int /*<<< orphan*/  NAU8825_REG_IMM_MODE_CTRL ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nau8825_xtalk_imm_stop(struct nau8825 *nau8825)
{
	/* Impedance measurement mode disable */
	regmap_update_bits(nau8825->regmap,
		NAU8825_REG_IMM_MODE_CTRL, NAU8825_IMM_EN, 0);
}