#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  tag; int /*<<< orphan*/  event; } ;
struct TYPE_4__ {scalar_t__ context; } ;
typedef  int /*<<< orphan*/  SV ;
typedef  int /*<<< orphan*/  HV ;
typedef  TYPE_1__* FunctionCallInfo ;
typedef  TYPE_2__ EventTriggerData ;

/* Variables and functions */
 int /*<<< orphan*/  cstr2sv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dTHX ; 
 int /*<<< orphan*/  hv_store_string (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * newHV () ; 
 int /*<<< orphan*/ * newRV_noinc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static SV  *
plperl_event_trigger_build_args(FunctionCallInfo fcinfo)
{
	dTHX;
	EventTriggerData *tdata;
	HV		   *hv;

	hv = newHV();

	tdata = (EventTriggerData *) fcinfo->context;

	hv_store_string(hv, "event", cstr2sv(tdata->event));
	hv_store_string(hv, "tag", cstr2sv(tdata->tag));

	return newRV_noinc((SV *) hv);
}