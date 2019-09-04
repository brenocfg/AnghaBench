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
typedef  int /*<<< orphan*/  u32 ;
typedef  enum bpf_type { ____Placeholder_bpf_type } bpf_type ;

/* Variables and functions */
 int BPF_TYPE_MAP ; 
 int BPF_TYPE_PROG ; 
 scalar_t__ IS_ERR (void*) ; 
 void* bpf_map_get_with_uref (int /*<<< orphan*/ ) ; 
 void* bpf_prog_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *bpf_fd_probe_obj(u32 ufd, enum bpf_type *type)
{
	void *raw;

	*type = BPF_TYPE_MAP;
	raw = bpf_map_get_with_uref(ufd);
	if (IS_ERR(raw)) {
		*type = BPF_TYPE_PROG;
		raw = bpf_prog_get(ufd);
	}

	return raw;
}