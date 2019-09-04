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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
struct machine {int dummy; } ;
struct cs_etm_queue {TYPE_1__* etm; } ;
struct TYPE_2__ {scalar_t__ kernel_start; struct machine* machine; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_RECORD_MISC_GUEST_KERNEL ; 
 int /*<<< orphan*/  PERF_RECORD_MISC_GUEST_USER ; 
 int /*<<< orphan*/  PERF_RECORD_MISC_HYPERVISOR ; 
 int /*<<< orphan*/  PERF_RECORD_MISC_KERNEL ; 
 int /*<<< orphan*/  PERF_RECORD_MISC_USER ; 
 scalar_t__ machine__is_host (struct machine*) ; 
 scalar_t__ perf_guest ; 

__attribute__((used)) static u8 cs_etm__cpu_mode(struct cs_etm_queue *etmq, u64 address)
{
	struct machine *machine;

	machine = etmq->etm->machine;

	if (address >= etmq->etm->kernel_start) {
		if (machine__is_host(machine))
			return PERF_RECORD_MISC_KERNEL;
		else
			return PERF_RECORD_MISC_GUEST_KERNEL;
	} else {
		if (machine__is_host(machine))
			return PERF_RECORD_MISC_USER;
		else if (perf_guest)
			return PERF_RECORD_MISC_GUEST_USER;
		else
			return PERF_RECORD_MISC_HYPERVISOR;
	}
}