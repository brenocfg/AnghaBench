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
struct brcmf_if {TYPE_2__* drvr; } ;
typedef  int /*<<< orphan*/  s8 ;
typedef  int /*<<< orphan*/  eventmask ;
struct TYPE_3__ {scalar_t__* evt_handler; } ;
struct TYPE_4__ {TYPE_1__ fweh; } ;

/* Variables and functions */
 int BRCMF_EVENTING_MASK_LEN ; 
 int BRCMF_E_IF ; 
 int BRCMF_E_LAST ; 
 int /*<<< orphan*/  EVENT ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  brcmf_err (char*,int) ; 
 int brcmf_fil_iovar_data_set (struct brcmf_if*,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  brcmf_fweh_event_name (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setbit (int /*<<< orphan*/ *,int) ; 

int brcmf_fweh_activate_events(struct brcmf_if *ifp)
{
	int i, err;
	s8 eventmask[BRCMF_EVENTING_MASK_LEN];

	memset(eventmask, 0, sizeof(eventmask));
	for (i = 0; i < BRCMF_E_LAST; i++) {
		if (ifp->drvr->fweh.evt_handler[i]) {
			brcmf_dbg(EVENT, "enable event %s\n",
				  brcmf_fweh_event_name(i));
			setbit(eventmask, i);
		}
	}

	/* want to handle IF event as well */
	brcmf_dbg(EVENT, "enable event IF\n");
	setbit(eventmask, BRCMF_E_IF);

	err = brcmf_fil_iovar_data_set(ifp, "event_msgs",
				       eventmask, BRCMF_EVENTING_MASK_LEN);
	if (err)
		brcmf_err("Set event_msgs error (%d)\n", err);

	return err;
}