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
struct nf_hook_state {scalar_t__ sk; scalar_t__ out; scalar_t__ in; } ;
struct nf_queue_entry {int /*<<< orphan*/  skb; struct nf_hook_state state; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_put (scalar_t__) ; 
 int /*<<< orphan*/  nf_queue_entry_release_br_nf_refs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_put (scalar_t__) ; 

void nf_queue_entry_release_refs(struct nf_queue_entry *entry)
{
	struct nf_hook_state *state = &entry->state;

	/* Release those devices we held, or Alexey will kill me. */
	if (state->in)
		dev_put(state->in);
	if (state->out)
		dev_put(state->out);
	if (state->sk)
		sock_put(state->sk);

	nf_queue_entry_release_br_nf_refs(entry->skb);
}