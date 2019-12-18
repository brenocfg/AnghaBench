#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct bpf_prog_offload {int /*<<< orphan*/  offloads; TYPE_2__* offdev; scalar_t__ dev_state; } ;
struct bpf_prog {TYPE_3__* aux; } ;
struct TYPE_6__ {struct bpf_prog_offload* offload; } ;
struct TYPE_5__ {TYPE_1__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* destroy ) (struct bpf_prog*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  bpf_prog_free_id (struct bpf_prog*,int) ; 
 int /*<<< orphan*/  kfree (struct bpf_prog_offload*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct bpf_prog*) ; 

__attribute__((used)) static void __bpf_prog_offload_destroy(struct bpf_prog *prog)
{
	struct bpf_prog_offload *offload = prog->aux->offload;

	if (offload->dev_state)
		offload->offdev->ops->destroy(prog);

	/* Make sure BPF_PROG_GET_NEXT_ID can't find this dead program */
	bpf_prog_free_id(prog, true);

	list_del_init(&offload->offloads);
	kfree(offload);
	prog->aux->offload = NULL;
}