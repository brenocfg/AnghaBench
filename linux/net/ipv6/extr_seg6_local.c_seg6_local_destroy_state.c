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
struct TYPE_4__ {int /*<<< orphan*/  prog; int /*<<< orphan*/  name; } ;
struct seg6_local_lwt {TYPE_2__ bpf; TYPE_1__* desc; int /*<<< orphan*/  srh; } ;
struct lwtunnel_state {int dummy; } ;
struct TYPE_3__ {int attrs; } ;

/* Variables and functions */
 int SEG6_LOCAL_BPF ; 
 int /*<<< orphan*/  bpf_prog_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct seg6_local_lwt* seg6_local_lwtunnel (struct lwtunnel_state*) ; 

__attribute__((used)) static void seg6_local_destroy_state(struct lwtunnel_state *lwt)
{
	struct seg6_local_lwt *slwt = seg6_local_lwtunnel(lwt);

	kfree(slwt->srh);

	if (slwt->desc->attrs & (1 << SEG6_LOCAL_BPF)) {
		kfree(slwt->bpf.name);
		bpf_prog_put(slwt->bpf.prog);
	}

	return;
}