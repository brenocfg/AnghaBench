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
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct rio_mport {scalar_t__ sys_size; } ;

/* Variables and functions */
 scalar_t__ RIO_GLOBAL_TABLE ; 
 int RIO_INVALID_ROUTE ; 
 int /*<<< orphan*/  RIO_PEF_CAR ; 
 int RIO_PEF_EXT_RT ; 
 int RIO_RT_MAX_DESTID ; 
 int /*<<< orphan*/  RIO_STD_RTE_CONF_DESTID_SEL_CSR ; 
 int /*<<< orphan*/  RIO_STD_RTE_CONF_PORT_SEL_CSR ; 
 int /*<<< orphan*/  RIO_SWITCH_RT_LIMIT ; 
 int /*<<< orphan*/  rio_mport_read_config_32 (struct rio_mport*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  rio_mport_write_config_32 (struct rio_mport*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
rio_std_route_clr_table(struct rio_mport *mport, u16 destid, u8 hopcount,
			u16 table)
{
	u32 max_destid = 0xff;
	u32 i, pef, id_inc = 1, ext_cfg = 0;
	u32 port_sel = RIO_INVALID_ROUTE;

	if (table == RIO_GLOBAL_TABLE) {
		rio_mport_read_config_32(mport, destid, hopcount,
					 RIO_PEF_CAR, &pef);

		if (mport->sys_size) {
			rio_mport_read_config_32(mport, destid, hopcount,
						 RIO_SWITCH_RT_LIMIT,
						 &max_destid);
			max_destid &= RIO_RT_MAX_DESTID;
		}

		if (pef & RIO_PEF_EXT_RT) {
			ext_cfg = 0x80000000;
			id_inc = 4;
			port_sel = (RIO_INVALID_ROUTE << 24) |
				   (RIO_INVALID_ROUTE << 16) |
				   (RIO_INVALID_ROUTE << 8) |
				   RIO_INVALID_ROUTE;
		}

		for (i = 0; i <= max_destid;) {
			rio_mport_write_config_32(mport, destid, hopcount,
					RIO_STD_RTE_CONF_DESTID_SEL_CSR,
					ext_cfg | i);
			rio_mport_write_config_32(mport, destid, hopcount,
					RIO_STD_RTE_CONF_PORT_SEL_CSR,
					port_sel);
			i += id_inc;
		}
	}

	udelay(10);
	return 0;
}