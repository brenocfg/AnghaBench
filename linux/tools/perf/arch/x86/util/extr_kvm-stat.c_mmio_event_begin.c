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
struct perf_sample {int dummy; } ;
struct evsel {int /*<<< orphan*/  name; } ;
struct event_key {int dummy; } ;

/* Variables and functions */
 scalar_t__ KVM_TRACE_MMIO_WRITE ; 
 scalar_t__ kvm_exit_event (struct evsel*) ; 
 int /*<<< orphan*/  mmio_event_get_key (struct evsel*,struct perf_sample*,struct event_key*) ; 
 scalar_t__ perf_evsel__intval (struct evsel*,struct perf_sample*,char*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool mmio_event_begin(struct evsel *evsel,
			     struct perf_sample *sample, struct event_key *key)
{
	/* MMIO read begin event in kernel. */
	if (kvm_exit_event(evsel))
		return true;

	/* MMIO write begin event in kernel. */
	if (!strcmp(evsel->name, "kvm:kvm_mmio") &&
	    perf_evsel__intval(evsel, sample, "type") == KVM_TRACE_MMIO_WRITE) {
		mmio_event_get_key(evsel, sample, key);
		return true;
	}

	return false;
}