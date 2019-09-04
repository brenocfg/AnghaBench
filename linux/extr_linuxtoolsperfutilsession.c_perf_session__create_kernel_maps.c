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
struct TYPE_2__ {int /*<<< orphan*/  host; } ;
struct perf_session {TYPE_1__ machines; } ;

/* Variables and functions */
 int machine__create_kernel_maps (int /*<<< orphan*/ *) ; 
 int machines__create_guest_kernel_maps (TYPE_1__*) ; 

int perf_session__create_kernel_maps(struct perf_session *session)
{
	int ret = machine__create_kernel_maps(&session->machines.host);

	if (ret >= 0)
		ret = machines__create_guest_kernel_maps(&session->machines);
	return ret;
}