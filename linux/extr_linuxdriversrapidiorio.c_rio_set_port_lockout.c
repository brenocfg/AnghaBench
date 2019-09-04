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
typedef  int /*<<< orphan*/  u32 ;
struct rio_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RIO_DEV_PORT_N_CTL_CSR (struct rio_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RIO_PORT_N_CTL_LOCKOUT ; 
 int /*<<< orphan*/  rio_read_config_32 (struct rio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rio_write_config_32 (struct rio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rio_set_port_lockout(struct rio_dev *rdev, u32 pnum, int lock)
{
	u32 regval;

	rio_read_config_32(rdev,
		RIO_DEV_PORT_N_CTL_CSR(rdev, pnum),
		&regval);
	if (lock)
		regval |= RIO_PORT_N_CTL_LOCKOUT;
	else
		regval &= ~RIO_PORT_N_CTL_LOCKOUT;

	rio_write_config_32(rdev,
		RIO_DEV_PORT_N_CTL_CSR(rdev, pnum),
		regval);
	return 0;
}