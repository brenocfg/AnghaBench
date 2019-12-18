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
typedef  enum bpf_type { ____Placeholder_bpf_type } bpf_type ;

/* Variables and functions */
#define  BPF_TYPE_MAP 129 
#define  BPF_TYPE_PROG 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 void* bpf_map_inc (void*,int) ; 
 void* bpf_prog_inc (void*) ; 

__attribute__((used)) static void *bpf_any_get(void *raw, enum bpf_type type)
{
	switch (type) {
	case BPF_TYPE_PROG:
		raw = bpf_prog_inc(raw);
		break;
	case BPF_TYPE_MAP:
		raw = bpf_map_inc(raw, true);
		break;
	default:
		WARN_ON_ONCE(1);
		break;
	}

	return raw;
}