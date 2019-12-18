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
struct bpf_func_state {int /*<<< orphan*/  acquired_refs; } ;

/* Variables and functions */
 int copy_reference_state (struct bpf_func_state*,struct bpf_func_state*) ; 
 int realloc_reference_state (struct bpf_func_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int transfer_reference_state(struct bpf_func_state *dst,
				    struct bpf_func_state *src)
{
	int err = realloc_reference_state(dst, src->acquired_refs, false);
	if (err)
		return err;
	err = copy_reference_state(dst, src);
	if (err)
		return err;
	return 0;
}