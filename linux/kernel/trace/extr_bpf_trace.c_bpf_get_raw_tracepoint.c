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
struct bpf_raw_event_map {TYPE_1__* tp; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct bpf_raw_event_map* __start__bpf_raw_tp ; 
 struct bpf_raw_event_map* __stop__bpf_raw_tp ; 
 struct bpf_raw_event_map* bpf_get_raw_tracepoint_module (char const*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

struct bpf_raw_event_map *bpf_get_raw_tracepoint(const char *name)
{
	struct bpf_raw_event_map *btp = __start__bpf_raw_tp;

	for (; btp < __stop__bpf_raw_tp; btp++) {
		if (!strcmp(btp->tp->name, name))
			return btp;
	}

	return bpf_get_raw_tracepoint_module(name);
}