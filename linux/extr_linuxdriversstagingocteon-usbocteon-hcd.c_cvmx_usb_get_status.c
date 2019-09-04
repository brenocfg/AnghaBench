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
struct TYPE_3__ {scalar_t__ prtconnsts; int /*<<< orphan*/  prtspd; int /*<<< orphan*/  prtpwr; int /*<<< orphan*/  prtovrcurract; int /*<<< orphan*/  prtena; } ;
union cvmx_usbcx_hprt {TYPE_1__ s; int /*<<< orphan*/  u32; } ;
struct TYPE_4__ {scalar_t__ connected; } ;
struct octeon_hcd {TYPE_2__ port_status; int /*<<< orphan*/  index; } ;
struct cvmx_usb_port_status {scalar_t__ connected; int connect_change; int /*<<< orphan*/  port_speed; int /*<<< orphan*/  port_powered; int /*<<< orphan*/  port_over_current; int /*<<< orphan*/  port_enabled; } ;
typedef  int /*<<< orphan*/  result ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_USBCX_HPRT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_usb_read_csr32 (struct octeon_hcd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct cvmx_usb_port_status*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct cvmx_usb_port_status cvmx_usb_get_status(struct octeon_hcd *usb)
{
	union cvmx_usbcx_hprt usbc_hprt;
	struct cvmx_usb_port_status result;

	memset(&result, 0, sizeof(result));

	usbc_hprt.u32 = cvmx_usb_read_csr32(usb, CVMX_USBCX_HPRT(usb->index));
	result.port_enabled = usbc_hprt.s.prtena;
	result.port_over_current = usbc_hprt.s.prtovrcurract;
	result.port_powered = usbc_hprt.s.prtpwr;
	result.port_speed = usbc_hprt.s.prtspd;
	result.connected = usbc_hprt.s.prtconnsts;
	result.connect_change =
		result.connected != usb->port_status.connected;

	return result;
}