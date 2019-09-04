#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct rio_mport {scalar_t__ sys_size; } ;
struct rio_dev {int /*<<< orphan*/  hopcount; int /*<<< orphan*/  destid; TYPE_2__* rswitch; TYPE_1__* net; } ;
struct TYPE_4__ {int /*<<< orphan*/ * route_table; } ;
struct TYPE_3__ {struct rio_mport* hport; } ;

/* Variables and functions */
 int /*<<< orphan*/  RIO_DEV_PORT_N_CTL_CSR (struct rio_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RIO_DEV_PORT_N_ERR_STS_CSR (struct rio_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RIO_DEV_PORT_N_MNT_RSP_CSR (struct rio_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RIO_GLOBAL_TABLE ; 
 int RIO_PORT_N_CTL_LOCKOUT ; 
 int RIO_PORT_N_ERR_STS_INP_ES ; 
 int RIO_PORT_N_ERR_STS_OUT_ES ; 
 int RIO_PORT_N_ERR_STS_PORT_OK ; 
 int RIO_PORT_N_MNT_RSP_RVAL ; 
 int /*<<< orphan*/  TSI578_SP_CS_TX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TSI578_SP_INT_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TSI578_SP_LUT_PEINF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  rio_name (struct rio_dev*) ; 
 int /*<<< orphan*/  rio_read_config_32 (struct rio_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  rio_write_config_32 (struct rio_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tsi57x_route_add_entry (struct rio_mport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
tsi57x_em_handler(struct rio_dev *rdev, u8 portnum)
{
	struct rio_mport *mport = rdev->net->hport;
	u32 intstat, err_status;
	int sendcount, checkcount;
	u8 route_port;
	u32 regval;

	rio_read_config_32(rdev,
			RIO_DEV_PORT_N_ERR_STS_CSR(rdev, portnum),
			&err_status);

	if ((err_status & RIO_PORT_N_ERR_STS_PORT_OK) &&
	    (err_status & (RIO_PORT_N_ERR_STS_OUT_ES |
			  RIO_PORT_N_ERR_STS_INP_ES))) {
		/* Remove any queued packets by locking/unlocking port */
		rio_read_config_32(rdev,
			RIO_DEV_PORT_N_CTL_CSR(rdev, portnum),
			&regval);
		if (!(regval & RIO_PORT_N_CTL_LOCKOUT)) {
			rio_write_config_32(rdev,
				RIO_DEV_PORT_N_CTL_CSR(rdev, portnum),
				regval | RIO_PORT_N_CTL_LOCKOUT);
			udelay(50);
			rio_write_config_32(rdev,
				RIO_DEV_PORT_N_CTL_CSR(rdev, portnum),
				regval);
		}

		/* Read from link maintenance response register to clear
		 * valid bit
		 */
		rio_read_config_32(rdev,
			RIO_DEV_PORT_N_MNT_RSP_CSR(rdev, portnum),
			&regval);

		/* Send a Packet-Not-Accepted/Link-Request-Input-Status control
		 * symbol to recover from IES/OES
		 */
		sendcount = 3;
		while (sendcount) {
			rio_write_config_32(rdev,
					  TSI578_SP_CS_TX(portnum), 0x40fc8000);
			checkcount = 3;
			while (checkcount--) {
				udelay(50);
				rio_read_config_32(rdev,
					RIO_DEV_PORT_N_MNT_RSP_CSR(rdev,
								   portnum),
					&regval);
				if (regval & RIO_PORT_N_MNT_RSP_RVAL)
					goto exit_es;
			}

			sendcount--;
		}
	}

exit_es:
	/* Clear implementation specific error status bits */
	rio_read_config_32(rdev, TSI578_SP_INT_STATUS(portnum), &intstat);
	pr_debug("TSI578[%x:%x] SP%d_INT_STATUS=0x%08x\n",
		 rdev->destid, rdev->hopcount, portnum, intstat);

	if (intstat & 0x10000) {
		rio_read_config_32(rdev,
				TSI578_SP_LUT_PEINF(portnum), &regval);
		regval = (mport->sys_size) ? (regval >> 16) : (regval >> 24);
		route_port = rdev->rswitch->route_table[regval];
		pr_debug("RIO: TSI578[%s] P%d LUT Parity Error (destID=%d)\n",
			rio_name(rdev), portnum, regval);
		tsi57x_route_add_entry(mport, rdev->destid, rdev->hopcount,
				RIO_GLOBAL_TABLE, regval, route_port);
	}

	rio_write_config_32(rdev, TSI578_SP_INT_STATUS(portnum),
			    intstat & 0x000700bd);

	return 0;
}