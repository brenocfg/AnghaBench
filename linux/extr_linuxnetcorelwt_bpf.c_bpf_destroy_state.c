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
struct lwtunnel_state {int dummy; } ;
struct bpf_lwt {int /*<<< orphan*/  xmit; int /*<<< orphan*/  out; int /*<<< orphan*/  in; } ;

/* Variables and functions */
 struct bpf_lwt* bpf_lwt_lwtunnel (struct lwtunnel_state*) ; 
 int /*<<< orphan*/  bpf_lwt_prog_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bpf_destroy_state(struct lwtunnel_state *lwt)
{
	struct bpf_lwt *bpf = bpf_lwt_lwtunnel(lwt);

	bpf_lwt_prog_destroy(&bpf->in);
	bpf_lwt_prog_destroy(&bpf->out);
	bpf_lwt_prog_destroy(&bpf->xmit);
}