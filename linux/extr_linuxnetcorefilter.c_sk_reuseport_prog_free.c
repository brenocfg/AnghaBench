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
struct bpf_prog {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ BPF_PROG_TYPE_SK_REUSEPORT ; 
 int /*<<< orphan*/  bpf_prog_destroy (struct bpf_prog*) ; 
 int /*<<< orphan*/  bpf_prog_put (struct bpf_prog*) ; 

void sk_reuseport_prog_free(struct bpf_prog *prog)
{
	if (!prog)
		return;

	if (prog->type == BPF_PROG_TYPE_SK_REUSEPORT)
		bpf_prog_put(prog);
	else
		bpf_prog_destroy(prog);
}