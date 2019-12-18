#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tep_handle {int dummy; } ;
struct TYPE_3__ {struct tep_handle* pevent; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEP_NSEC_OUTPUT ; 
 int tep_is_bigendian () ; 
 int /*<<< orphan*/  tep_set_file_bigendian (struct tep_handle*,int) ; 
 int /*<<< orphan*/  tep_set_flag (struct tep_handle*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tep_set_local_bigendian (struct tep_handle*,int) ; 
 TYPE_1__ tevent ; 
 int tevent_initialized ; 
 scalar_t__ trace_event__init (TYPE_1__*) ; 

__attribute__((used)) static int trace_event__init2(void)
{
	int be = tep_is_bigendian();
	struct tep_handle *pevent;

	if (trace_event__init(&tevent))
		return -1;

	pevent = tevent.pevent;
	tep_set_flag(pevent, TEP_NSEC_OUTPUT);
	tep_set_file_bigendian(pevent, be);
	tep_set_local_bigendian(pevent, be);
	tevent_initialized = true;
	return 0;
}