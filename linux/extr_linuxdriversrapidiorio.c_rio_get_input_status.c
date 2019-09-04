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
struct rio_dev {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  RIO_DEV_PORT_N_MNT_REQ_CSR (struct rio_dev*,int) ; 
 int /*<<< orphan*/  RIO_DEV_PORT_N_MNT_RSP_CSR (struct rio_dev*,int) ; 
 int /*<<< orphan*/  RIO_MNT_REQ_CMD_IS ; 
 int RIO_PORT_N_MNT_RSP_RVAL ; 
 int /*<<< orphan*/  rio_read_config_32 (struct rio_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  rio_write_config_32 (struct rio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
rio_get_input_status(struct rio_dev *rdev, int pnum, u32 *lnkresp)
{
	u32 regval;
	int checkcount;

	if (lnkresp) {
		/* Read from link maintenance response register
		 * to clear valid bit */
		rio_read_config_32(rdev,
			RIO_DEV_PORT_N_MNT_RSP_CSR(rdev, pnum),
			&regval);
		udelay(50);
	}

	/* Issue Input-status command */
	rio_write_config_32(rdev,
		RIO_DEV_PORT_N_MNT_REQ_CSR(rdev, pnum),
		RIO_MNT_REQ_CMD_IS);

	/* Exit if the response is not expected */
	if (!lnkresp)
		return 0;

	checkcount = 3;
	while (checkcount--) {
		udelay(50);
		rio_read_config_32(rdev,
			RIO_DEV_PORT_N_MNT_RSP_CSR(rdev, pnum),
			&regval);
		if (regval & RIO_PORT_N_MNT_RSP_RVAL) {
			*lnkresp = regval;
			return 0;
		}
	}

	return -EIO;
}