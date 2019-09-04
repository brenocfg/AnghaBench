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
struct isci_phy {int max_negotiated_speed; } ;
typedef  enum sas_linkrate { ____Placeholder_sas_linkrate } sas_linkrate ;

/* Variables and functions */

enum sas_linkrate sci_phy_linkrate(struct isci_phy *iphy)
{
	return iphy->max_negotiated_speed;
}