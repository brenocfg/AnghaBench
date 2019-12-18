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
struct TYPE_4__ {int size; } ;
union perf_event {TYPE_2__ header; } ;
struct perf_sample {int raw_size; scalar_t__ raw_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  attr; } ;
struct evsel {TYPE_1__ core; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER ; 
 int /*<<< orphan*/  FREETMPS ; 
 int /*<<< orphan*/  G_SCALAR ; 
 int /*<<< orphan*/  LEAVE ; 
 int /*<<< orphan*/  PUSHMARK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUTBACK ; 
 int /*<<< orphan*/  SAVETMPS ; 
 int /*<<< orphan*/  SP ; 
 int /*<<< orphan*/  SPAGAIN ; 
 int /*<<< orphan*/  XPUSHs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  call_pv (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dSP ; 
 int /*<<< orphan*/  get_cv (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  newSVpvn (char const*,int) ; 
 int /*<<< orphan*/  sv_2mortal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void perl_process_event_generic(union perf_event *event,
				       struct perf_sample *sample,
				       struct evsel *evsel)
{
	dSP;

	if (!get_cv("process_event", 0))
		return;

	ENTER;
	SAVETMPS;
	PUSHMARK(SP);
	XPUSHs(sv_2mortal(newSVpvn((const char *)event, event->header.size)));
	XPUSHs(sv_2mortal(newSVpvn((const char *)&evsel->core.attr, sizeof(evsel->core.attr))));
	XPUSHs(sv_2mortal(newSVpvn((const char *)sample, sizeof(*sample))));
	XPUSHs(sv_2mortal(newSVpvn((const char *)sample->raw_data, sample->raw_size)));
	PUTBACK;
	call_pv("process_event", G_SCALAR);
	SPAGAIN;
	PUTBACK;
	FREETMPS;
	LEAVE;
}