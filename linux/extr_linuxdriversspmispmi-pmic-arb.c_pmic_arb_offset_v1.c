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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct spmi_pmic_arb {int channel; } ;
typedef  enum pmic_arb_channel { ____Placeholder_pmic_arb_channel } pmic_arb_channel ;

/* Variables and functions */

__attribute__((used)) static int pmic_arb_offset_v1(struct spmi_pmic_arb *pmic_arb, u8 sid, u16 addr,
			enum pmic_arb_channel ch_type)
{
	return 0x800 + 0x80 * pmic_arb->channel;
}