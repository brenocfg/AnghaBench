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
struct TYPE_2__ {int /*<<< orphan*/ ** evt_handler; } ;
struct brcmf_pub {TYPE_1__ fweh; } ;
typedef  enum brcmf_fweh_event_code { ____Placeholder_brcmf_fweh_event_code } brcmf_fweh_event_code ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_fweh_event_name (int) ; 

void brcmf_fweh_unregister(struct brcmf_pub *drvr,
			   enum brcmf_fweh_event_code code)
{
	brcmf_dbg(TRACE, "event handler cleared for %s\n",
		  brcmf_fweh_event_name(code));
	drvr->fweh.evt_handler[code] = NULL;
}