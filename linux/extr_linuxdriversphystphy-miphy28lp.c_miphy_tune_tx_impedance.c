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
struct miphy28lp_phy {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ MIPHY_COMP_POSTP ; 
 int /*<<< orphan*/  writeb_relaxed (int,scalar_t__) ; 

__attribute__((used)) static inline void miphy_tune_tx_impedance(struct miphy28lp_phy *miphy_phy)
{
	/* Compensate Tx impedance to avoid out of range values */
	writeb_relaxed(0x02, miphy_phy->base + MIPHY_COMP_POSTP);
}