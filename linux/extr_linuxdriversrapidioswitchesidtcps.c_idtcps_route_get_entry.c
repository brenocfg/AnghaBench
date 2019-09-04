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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct rio_mport {int dummy; } ;

/* Variables and functions */
 scalar_t__ CPS_DEFAULT_ROUTE ; 
 scalar_t__ CPS_NO_ROUTE ; 
 scalar_t__ RIO_GLOBAL_TABLE ; 
 scalar_t__ RIO_INVALID_ROUTE ; 
 int /*<<< orphan*/  RIO_STD_RTE_CONF_DESTID_SEL_CSR ; 
 int /*<<< orphan*/  RIO_STD_RTE_CONF_PORT_SEL_CSR ; 
 int /*<<< orphan*/  rio_mport_read_config_32 (struct rio_mport*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  rio_mport_write_config_32 (struct rio_mport*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
idtcps_route_get_entry(struct rio_mport *mport, u16 destid, u8 hopcount,
		       u16 table, u16 route_destid, u8 *route_port)
{
	u32 result;

	if (table == RIO_GLOBAL_TABLE) {
		rio_mport_write_config_32(mport, destid, hopcount,
				RIO_STD_RTE_CONF_DESTID_SEL_CSR, route_destid);

		rio_mport_read_config_32(mport, destid, hopcount,
				RIO_STD_RTE_CONF_PORT_SEL_CSR, &result);

		if (CPS_DEFAULT_ROUTE == (u8)result ||
		    CPS_NO_ROUTE == (u8)result)
			*route_port = RIO_INVALID_ROUTE;
		else
			*route_port = (u8)result;
	}

	return 0;
}