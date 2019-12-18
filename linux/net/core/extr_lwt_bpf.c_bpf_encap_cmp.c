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
 scalar_t__ bpf_lwt_prog_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bpf_encap_cmp(struct lwtunnel_state *a, struct lwtunnel_state *b)
{
	struct bpf_lwt *a_bpf = bpf_lwt_lwtunnel(a);
	struct bpf_lwt *b_bpf = bpf_lwt_lwtunnel(b);

	return bpf_lwt_prog_cmp(&a_bpf->in, &b_bpf->in) ||
	       bpf_lwt_prog_cmp(&a_bpf->out, &b_bpf->out) ||
	       bpf_lwt_prog_cmp(&a_bpf->xmit, &b_bpf->xmit);
}