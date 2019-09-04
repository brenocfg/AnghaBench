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
struct parport {int dummy; } ;
struct ax_drvdata {int /*<<< orphan*/  dev; int /*<<< orphan*/  spp_cpr; } ;

/* Variables and functions */
 unsigned int AX_CPR_ATFD ; 
 unsigned int AX_CPR_SLCTIN ; 
 unsigned int AX_CPR_STRB ; 
 unsigned int AX_CPR_nDOE ; 
 unsigned int AX_CPR_nINIT ; 
 unsigned char PARPORT_CONTROL_AUTOFD ; 
 unsigned char PARPORT_CONTROL_INIT ; 
 unsigned char PARPORT_CONTROL_SELECT ; 
 unsigned char PARPORT_CONTROL_STROBE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned char,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned char,unsigned char) ; 
 unsigned char parport_ax88796_read_control (struct parport*) ; 
 struct ax_drvdata* pp_to_drv (struct parport*) ; 
 unsigned int readb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeb (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
parport_ax88796_write_control(struct parport *p, unsigned char control)
{
	struct ax_drvdata *dd = pp_to_drv(p);
	unsigned int cpr = readb(dd->spp_cpr);

	cpr &= AX_CPR_nDOE;

	if (!(control & PARPORT_CONTROL_STROBE))
		cpr |= AX_CPR_STRB;

	if (!(control & PARPORT_CONTROL_AUTOFD))
		cpr |= AX_CPR_ATFD;

	if (control & PARPORT_CONTROL_INIT)
		cpr |= AX_CPR_nINIT;

	if (!(control & PARPORT_CONTROL_SELECT))
		cpr |= AX_CPR_SLCTIN;

	dev_dbg(dd->dev, "write_control: ctrl=%02x, cpr=%02x\n", control, cpr);
	writeb(cpr, dd->spp_cpr);

	if (parport_ax88796_read_control(p) != control) {
		dev_err(dd->dev, "write_control: read != set (%02x, %02x)\n",
			parport_ax88796_read_control(p), control);
	}
}