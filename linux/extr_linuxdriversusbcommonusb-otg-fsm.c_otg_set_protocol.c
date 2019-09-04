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
struct otg_fsm {int protocol; } ;

/* Variables and functions */
 int PROTO_GADGET ; 
 int PROTO_HOST ; 
 int /*<<< orphan*/  VDBG (char*,int,int) ; 
 int otg_start_gadget (struct otg_fsm*,int) ; 
 int otg_start_host (struct otg_fsm*,int) ; 

__attribute__((used)) static int otg_set_protocol(struct otg_fsm *fsm, int protocol)
{
	int ret = 0;

	if (fsm->protocol != protocol) {
		VDBG("Changing role fsm->protocol= %d; new protocol= %d\n",
			fsm->protocol, protocol);
		/* stop old protocol */
		if (fsm->protocol == PROTO_HOST)
			ret = otg_start_host(fsm, 0);
		else if (fsm->protocol == PROTO_GADGET)
			ret = otg_start_gadget(fsm, 0);
		if (ret)
			return ret;

		/* start new protocol */
		if (protocol == PROTO_HOST)
			ret = otg_start_host(fsm, 1);
		else if (protocol == PROTO_GADGET)
			ret = otg_start_gadget(fsm, 1);
		if (ret)
			return ret;

		fsm->protocol = protocol;
		return 0;
	}

	return 0;
}