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
struct bpf_raw_event_map {scalar_t__ bpf_func; int /*<<< orphan*/  tp; } ;
struct bpf_prog {int dummy; } ;

/* Variables and functions */
 int tracepoint_probe_unregister (int /*<<< orphan*/ ,void*,struct bpf_prog*) ; 

int bpf_probe_unregister(struct bpf_raw_event_map *btp, struct bpf_prog *prog)
{
	return tracepoint_probe_unregister(btp->tp, (void *)btp->bpf_func, prog);
}