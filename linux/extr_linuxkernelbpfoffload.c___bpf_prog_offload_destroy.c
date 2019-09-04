#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct bpf_prog* prog; } ;
struct netdev_bpf {TYPE_1__ offload; } ;
struct bpf_prog_offload {int /*<<< orphan*/  offloads; scalar_t__ dev_state; } ;
struct bpf_prog {TYPE_2__* aux; } ;
struct TYPE_4__ {struct bpf_prog_offload* offload; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_OFFLOAD_DESTROY ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __bpf_offload_ndo (struct bpf_prog*,int /*<<< orphan*/ ,struct netdev_bpf*) ; 
 int /*<<< orphan*/  bpf_prog_free_id (struct bpf_prog*,int) ; 
 int /*<<< orphan*/  kfree (struct bpf_prog_offload*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __bpf_prog_offload_destroy(struct bpf_prog *prog)
{
	struct bpf_prog_offload *offload = prog->aux->offload;
	struct netdev_bpf data = {};

	data.offload.prog = prog;

	if (offload->dev_state)
		WARN_ON(__bpf_offload_ndo(prog, BPF_OFFLOAD_DESTROY, &data));

	/* Make sure BPF_PROG_GET_NEXT_ID can't find this dead program */
	bpf_prog_free_id(prog, true);

	list_del_init(&offload->offloads);
	kfree(offload);
	prog->aux->offload = NULL;
}