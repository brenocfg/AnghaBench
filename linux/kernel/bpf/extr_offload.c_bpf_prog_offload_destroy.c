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
struct TYPE_2__ {scalar_t__ offload; } ;

/* Variables and functions */
 int /*<<< orphan*/  __bpf_prog_offload_destroy (struct bpf_prog*) ; 
 int /*<<< orphan*/  bpf_devs_lock ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void bpf_prog_offload_destroy(struct bpf_prog *prog)
{
	down_write(&bpf_devs_lock);
	if (prog->aux->offload)
		__bpf_prog_offload_destroy(prog);
	up_write(&bpf_devs_lock);
}