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
struct rio_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RIO_DEV_PORT_N_ERR_STS_CSR (struct rio_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RIO_PLM_SPx_IMP_SPEC_CTL (int /*<<< orphan*/ ) ; 
 int RIO_PLM_SPx_IMP_SPEC_CTL_SOFT_RST ; 
 int RIO_PORT_N_ERR_STS_INP_ES ; 
 int RIO_PORT_N_ERR_STS_OUT_ES ; 
 int RIO_PORT_N_ERR_STS_PORT_UNINIT ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  rio_read_config_32 (struct rio_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  rio_write_config_32 (struct rio_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
idtg3_em_handler(struct rio_dev *rdev, u8 pnum)
{
	u32 err_status;
	u32 rval;

	rio_read_config_32(rdev,
			RIO_DEV_PORT_N_ERR_STS_CSR(rdev, pnum),
			&err_status);

	/* Do nothing for device/link removal */
	if (err_status & RIO_PORT_N_ERR_STS_PORT_UNINIT)
		return 0;

	/* When link is OK we have a device insertion.
	 * Request port soft reset to clear errors if they present.
	 * Inbound and outbound ackIDs will be 0 after reset.
	 */
	if (err_status & (RIO_PORT_N_ERR_STS_OUT_ES |
				RIO_PORT_N_ERR_STS_INP_ES)) {
		rio_read_config_32(rdev, RIO_PLM_SPx_IMP_SPEC_CTL(pnum), &rval);
		rio_write_config_32(rdev, RIO_PLM_SPx_IMP_SPEC_CTL(pnum),
				    rval | RIO_PLM_SPx_IMP_SPEC_CTL_SOFT_RST);
		udelay(10);
		rio_write_config_32(rdev, RIO_PLM_SPx_IMP_SPEC_CTL(pnum), rval);
		msleep(500);
	}

	return 0;
}