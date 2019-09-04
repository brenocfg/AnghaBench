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
struct aic32x4_priv {int /*<<< orphan*/  supply_av; int /*<<< orphan*/  supply_dv; int /*<<< orphan*/  supply_ldo; int /*<<< orphan*/  supply_iov; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void aic32x4_disable_regulators(struct aic32x4_priv *aic32x4)
{
	regulator_disable(aic32x4->supply_iov);

	if (!IS_ERR(aic32x4->supply_ldo))
		regulator_disable(aic32x4->supply_ldo);

	if (!IS_ERR(aic32x4->supply_dv))
		regulator_disable(aic32x4->supply_dv);

	if (!IS_ERR(aic32x4->supply_av))
		regulator_disable(aic32x4->supply_av);
}