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

/* Variables and functions */
 int /*<<< orphan*/  BPF_LOADER_ERRNO__OBJCONF_MAP_EVTDIM ; 
 int /*<<< orphan*/  BPF_LOADER_ERRNO__OBJCONF_MAP_EVTINH ; 
 int /*<<< orphan*/  BPF_LOADER_ERRNO__OBJCONF_MAP_EVTTYPE ; 
 int /*<<< orphan*/  bpf__strerror_end (char*,size_t) ; 
 int /*<<< orphan*/  bpf__strerror_entry (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  bpf__strerror_head (int,char*,size_t) ; 
 int /*<<< orphan*/  emsg ; 

int bpf__strerror_apply_obj_config(int err, char *buf, size_t size)
{
	bpf__strerror_head(err, buf, size);
	bpf__strerror_entry(BPF_LOADER_ERRNO__OBJCONF_MAP_EVTDIM,
			    "Cannot set event to BPF map in multi-thread tracing");
	bpf__strerror_entry(BPF_LOADER_ERRNO__OBJCONF_MAP_EVTINH,
			    "%s (Hint: use -i to turn off inherit)", emsg);
	bpf__strerror_entry(BPF_LOADER_ERRNO__OBJCONF_MAP_EVTTYPE,
			    "Can only put raw, hardware and BPF output event into a BPF map");
	bpf__strerror_end(buf, size);
	return 0;
}