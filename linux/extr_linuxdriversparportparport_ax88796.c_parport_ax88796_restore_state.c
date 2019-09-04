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
struct TYPE_3__ {int /*<<< orphan*/  cpr; } ;
struct TYPE_4__ {TYPE_1__ ax88796; } ;
struct parport_state {TYPE_2__ u; } ;
struct parport {int dummy; } ;
struct ax_drvdata {int /*<<< orphan*/  spp_cpr; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,struct parport*,struct parport_state*) ; 
 struct ax_drvdata* pp_to_drv (struct parport*) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
parport_ax88796_restore_state(struct parport *p, struct parport_state *s)
{
	struct ax_drvdata *dd = pp_to_drv(p);

	dev_dbg(dd->dev, "restore_state: %p: state=%p\n", p, s);
	writeb(s->u.ax88796.cpr, dd->spp_cpr);
}