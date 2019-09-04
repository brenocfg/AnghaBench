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
typedef  int u16 ;
struct pnp_docking_station_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PNP_DS ; 
 int PNP_FUNCTION_NOT_SUPPORTED ; 
 int /*<<< orphan*/  PNP_GET_DOCKING_STATION_INFORMATION ; 
 int /*<<< orphan*/  PNP_TS1 ; 
 int call_pnp_bios (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pnp_docking_station_info*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnp_bios_present () ; 

int pnp_bios_dock_station_info(struct pnp_docking_station_info *data)
{
	u16 status;

	if (!pnp_bios_present())
		return PNP_FUNCTION_NOT_SUPPORTED;
	status = call_pnp_bios(PNP_GET_DOCKING_STATION_INFORMATION, 0, PNP_TS1,
			       PNP_DS, 0, 0, 0, 0, data,
			       sizeof(struct pnp_docking_station_info), NULL,
			       0);
	return status;
}