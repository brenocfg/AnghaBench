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
struct TYPE_3__ {int sid; scalar_t__ stype; int /*<<< orphan*/  type; } ;
struct vio_vcc {TYPE_1__ tag; } ;
struct TYPE_4__ {int /*<<< orphan*/  lp; } ;
struct vcc_port {TYPE_2__ vio; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIO_TYPE_CTRL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int ldc_write (int /*<<< orphan*/ ,struct vio_vcc*,int) ; 
 int /*<<< orphan*/  vccdbg (char*,int,int) ; 

__attribute__((used)) static int vcc_send_ctl(struct vcc_port *port, int ctl)
{
	struct vio_vcc pkt;
	int rv;

	pkt.tag.type = VIO_TYPE_CTRL;
	pkt.tag.sid = ctl;
	pkt.tag.stype = 0;

	rv = ldc_write(port->vio.lp, &pkt, sizeof(pkt.tag));
	WARN_ON(!rv);
	vccdbg("VCC: ldc_write(%ld)=%d\n", sizeof(pkt.tag), rv);

	return rv;
}