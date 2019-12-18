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
struct perf_kvm_stat {char* exit_reasons_isa; int /*<<< orphan*/  exit_reasons; } ;
struct evlist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hv_exit_reasons ; 
 int is_tracepoint_available (char const*,struct evlist*) ; 
 char** kvm_events_tp ; 
 char* kvm_exit_reason ; 
 char** ppc_book3s_hv_kvm_tp ; 

__attribute__((used)) static int ppc__setup_book3s_hv(struct perf_kvm_stat *kvm,
				struct evlist *evlist)
{
	const char **events_ptr;
	int i, nr_tp = 0, err = -1;

	/* Check for book3s_hv tracepoints */
	for (events_ptr = ppc_book3s_hv_kvm_tp; *events_ptr; events_ptr++) {
		err = is_tracepoint_available(*events_ptr, evlist);
		if (err)
			return -1;
		nr_tp++;
	}

	for (i = 0; i < nr_tp; i++)
		kvm_events_tp[i] = ppc_book3s_hv_kvm_tp[i];

	kvm_events_tp[i] = NULL;
	kvm_exit_reason = "trap";
	kvm->exit_reasons = hv_exit_reasons;
	kvm->exit_reasons_isa = "HV";

	return 0;
}