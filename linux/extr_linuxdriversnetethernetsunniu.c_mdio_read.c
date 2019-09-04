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
struct niu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_ADDR_OP (int,int,int) ; 
 int /*<<< orphan*/  MDIO_READ_OP (int,int) ; 
 int /*<<< orphan*/  MIF_FRAME_OUTPUT ; 
 int mdio_wait (struct niu*) ; 
 int /*<<< orphan*/  nw64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mdio_read(struct niu *np, int port, int dev, int reg)
{
	int err;

	nw64(MIF_FRAME_OUTPUT, MDIO_ADDR_OP(port, dev, reg));
	err = mdio_wait(np);
	if (err < 0)
		return err;

	nw64(MIF_FRAME_OUTPUT, MDIO_READ_OP(port, dev));
	return mdio_wait(np);
}