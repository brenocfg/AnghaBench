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
typedef  scalar_t__ u16 ;
struct r8152 {int dummy; } ;
struct ethtool_eee {int /*<<< orphan*/  eee_enabled; int /*<<< orphan*/  advertised; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_AN_EEE_ADV ; 
 int /*<<< orphan*/  MDIO_MMD_AN ; 
 scalar_t__ ethtool_adv_to_mmd_eee_adv_t (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8152_eee_en (struct r8152*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8152_mmd_write (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int r8152_set_eee(struct r8152 *tp, struct ethtool_eee *eee)
{
	u16 val = ethtool_adv_to_mmd_eee_adv_t(eee->advertised);

	r8152_eee_en(tp, eee->eee_enabled);

	if (!eee->eee_enabled)
		val = 0;

	r8152_mmd_write(tp, MDIO_MMD_AN, MDIO_AN_EEE_ADV, val);

	return 0;
}