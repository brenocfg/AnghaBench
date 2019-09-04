#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hvsi_priv {unsigned short mctrl; int /*<<< orphan*/  termno; } ;
struct TYPE_2__ {int len; int /*<<< orphan*/  type; } ;
struct hvsi_control {TYPE_1__ hdr; void* word; void* mask; int /*<<< orphan*/  verb; } ;

/* Variables and functions */
 int /*<<< orphan*/  HVSI_TSDTR ; 
 unsigned short TIOCM_DTR ; 
 int /*<<< orphan*/  VSV_SET_MODEM_CTL ; 
 int /*<<< orphan*/  VS_CONTROL_PACKET_HEADER ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int hvsi_send_packet (struct hvsi_priv*,TYPE_1__*) ; 
 int /*<<< orphan*/  pr_devel (char*,int /*<<< orphan*/ ,char*) ; 

int hvsilib_write_mctrl(struct hvsi_priv *pv, int dtr)
{
	struct hvsi_control ctrl;
	unsigned short mctrl;

	mctrl = pv->mctrl;
	if (dtr)
		mctrl |= TIOCM_DTR;
	else
		mctrl &= ~TIOCM_DTR;
	if (mctrl == pv->mctrl)
		return 0;
	pv->mctrl = mctrl;

	pr_devel("HVSI@%x: %s DTR...\n", pv->termno,
		 dtr ? "Setting" : "Clearing");

	ctrl.hdr.type = VS_CONTROL_PACKET_HEADER,
	ctrl.hdr.len = sizeof(struct hvsi_control);
	ctrl.verb = cpu_to_be16(VSV_SET_MODEM_CTL);
	ctrl.mask = cpu_to_be32(HVSI_TSDTR);
	ctrl.word = cpu_to_be32(dtr ? HVSI_TSDTR : 0);
	return hvsi_send_packet(pv, &ctrl.hdr);
}