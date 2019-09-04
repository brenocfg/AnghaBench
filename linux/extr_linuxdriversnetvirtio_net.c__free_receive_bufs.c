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
struct virtnet_info {int max_queue_pairs; TYPE_1__* rq; } ;
struct bpf_prog {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  xdp_prog; scalar_t__ pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __free_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_prog_put (struct bpf_prog*) ; 
 int /*<<< orphan*/  get_a_page (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct bpf_prog* rtnl_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _free_receive_bufs(struct virtnet_info *vi)
{
	struct bpf_prog *old_prog;
	int i;

	for (i = 0; i < vi->max_queue_pairs; i++) {
		while (vi->rq[i].pages)
			__free_pages(get_a_page(&vi->rq[i], GFP_KERNEL), 0);

		old_prog = rtnl_dereference(vi->rq[i].xdp_prog);
		RCU_INIT_POINTER(vi->rq[i].xdp_prog, NULL);
		if (old_prog)
			bpf_prog_put(old_prog);
	}
}