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
struct intelfb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DVOA ; 
 int DVOA_PORT ; 
 int /*<<< orphan*/  DVOB ; 
 int DVOB_PORT ; 
 int /*<<< orphan*/  DVOC ; 
 int DVOC_PORT ; 
 int INREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LVDS ; 
 int LVDS_PORT ; 
 int PORT_ENABLE ; 

int intelfbhw_check_non_crt(struct intelfb_info *dinfo)
{
	int dvo = 0;

	if (INREG(LVDS) & PORT_ENABLE)
		dvo |= LVDS_PORT;
	if (INREG(DVOA) & PORT_ENABLE)
		dvo |= DVOA_PORT;
	if (INREG(DVOB) & PORT_ENABLE)
		dvo |= DVOB_PORT;
	if (INREG(DVOC) & PORT_ENABLE)
		dvo |= DVOC_PORT;

	return dvo;
}