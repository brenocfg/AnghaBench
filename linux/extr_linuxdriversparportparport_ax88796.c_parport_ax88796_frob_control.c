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
struct ax_drvdata {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned char,unsigned char,unsigned char) ; 
 unsigned char parport_ax88796_read_control (struct parport*) ; 
 int /*<<< orphan*/  parport_ax88796_write_control (struct parport*,unsigned char) ; 
 struct ax_drvdata* pp_to_drv (struct parport*) ; 

__attribute__((used)) static unsigned char
parport_ax88796_frob_control(struct parport *p, unsigned char mask,
			     unsigned char val)
{
	struct ax_drvdata *dd = pp_to_drv(p);
	unsigned char old = parport_ax88796_read_control(p);

	dev_dbg(dd->dev, "frob: mask=%02x, val=%02x, old=%02x\n",
		mask, val, old);

	parport_ax88796_write_control(p, (old & ~mask) | val);
	return old;
}