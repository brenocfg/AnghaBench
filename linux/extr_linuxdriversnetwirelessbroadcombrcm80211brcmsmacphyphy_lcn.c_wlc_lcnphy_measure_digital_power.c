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
typedef  int u32 ;
typedef  int u16 ;
struct lcnphy_iq_est {int i_pwr; int q_pwr; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct brcms_phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  wlc_lcnphy_rx_iq_est (struct brcms_phy*,int,int,struct lcnphy_iq_est*) ; 

__attribute__((used)) static u32 wlc_lcnphy_measure_digital_power(struct brcms_phy *pi, u16 nsamples)
{
	struct lcnphy_iq_est iq_est = { 0, 0, 0 };

	if (!wlc_lcnphy_rx_iq_est(pi, nsamples, 32, &iq_est))
		return 0;
	return (iq_est.i_pwr + iq_est.q_pwr) / nsamples;
}