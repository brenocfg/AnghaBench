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
struct pm8001_mpi3_phy_pg_trx_config {int LaneLosCfg; int LanePgaCfg1; int LanePisoCfg1; int LanePisoCfg2; int LanePisoCfg3; int LanePisoCfg4; int LanePisoCfg5; int LanePisoCfg6; int LaneBctCtrl; } ;
struct pm8001_hba_info {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static
void pm8001_get_internal_phy_settings(struct pm8001_hba_info *pm8001_ha,
		struct pm8001_mpi3_phy_pg_trx_config *phycfg)
{
	phycfg->LaneLosCfg   = 0x00000132;
	phycfg->LanePgaCfg1  = 0x00203949;
	phycfg->LanePisoCfg1 = 0x000000FF;
	phycfg->LanePisoCfg2 = 0xFF000001;
	phycfg->LanePisoCfg3 = 0xE7011300;
	phycfg->LanePisoCfg4 = 0x631C40C0;
	phycfg->LanePisoCfg5 = 0xF8102036;
	phycfg->LanePisoCfg6 = 0xF74A1000;
	phycfg->LaneBctCtrl  = 0x00FB33F8;
}