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
struct bpf_prog {TYPE_1__* aux; } ;
struct TYPE_2__ {int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_BPF_EVENT_PROG_UNLOAD ; 
 int /*<<< orphan*/  __bpf_prog_put_noref (struct bpf_prog*,int) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bpf_prog_free_id (struct bpf_prog*,int) ; 
 int /*<<< orphan*/  perf_event_bpf_event (struct bpf_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __bpf_prog_put(struct bpf_prog *prog, bool do_idr_lock)
{
	if (atomic_dec_and_test(&prog->aux->refcnt)) {
		perf_event_bpf_event(prog, PERF_BPF_EVENT_PROG_UNLOAD, 0);
		/* bpf_prog_free_id() must be called first */
		bpf_prog_free_id(prog, do_idr_lock);
		__bpf_prog_put_noref(prog, true);
	}
}