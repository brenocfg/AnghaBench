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
typedef  int /*<<< orphan*/  u16 ;
struct brcms_phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  write_phy_reg (struct brcms_phy*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
wlc_phy_write_txmacreg_nphy(struct brcms_phy *pi, u16 holdoff, u16 delay)
{
	write_phy_reg(pi, 0x77, holdoff);
	write_phy_reg(pi, 0xb4, delay);
}