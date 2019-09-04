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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct rio_mport {int dummy; } ;

/* Variables and functions */
 int RIO_GLOBAL_TABLE ; 
 int /*<<< orphan*/  RIO_SWP_INFO_CAR ; 
 int RIO_SWP_INFO_PORT_NUM_MASK ; 
 int /*<<< orphan*/  SPP_ROUTE_CFG_DESTID (int) ; 
 int /*<<< orphan*/  SPP_ROUTE_CFG_PORT (int) ; 
 int /*<<< orphan*/  rio_mport_read_config_32 (struct rio_mport*,int,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  rio_mport_write_config_32 (struct rio_mport*,int,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
tsi57x_route_get_entry(struct rio_mport *mport, u16 destid, u8 hopcount,
		       u16 table, u16 route_destid, u8 *route_port)
{
	int ret = 0;
	u32 result;

	if (table == RIO_GLOBAL_TABLE) {
		/* Use local RT of the ingress port to avoid possible
		   race condition */
		rio_mport_read_config_32(mport, destid, hopcount,
			RIO_SWP_INFO_CAR, &result);
		table = (result & RIO_SWP_INFO_PORT_NUM_MASK);
	}

	rio_mport_write_config_32(mport, destid, hopcount,
				SPP_ROUTE_CFG_DESTID(table), route_destid);
	rio_mport_read_config_32(mport, destid, hopcount,
				SPP_ROUTE_CFG_PORT(table), &result);

	*route_port = (u8)result;
	if (*route_port > 15)
		ret = -1;

	return ret;
}