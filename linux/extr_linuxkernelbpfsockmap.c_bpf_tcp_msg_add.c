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
struct sock {int dummy; } ;
struct smap_psock {int /*<<< orphan*/  bpf_tx_msg; } ;
struct bpf_prog {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bpf_prog_put (struct bpf_prog*) ; 
 struct bpf_prog* xchg (int /*<<< orphan*/ *,struct bpf_prog*) ; 

__attribute__((used)) static void bpf_tcp_msg_add(struct smap_psock *psock,
			    struct sock *sk,
			    struct bpf_prog *tx_msg)
{
	struct bpf_prog *orig_tx_msg;

	orig_tx_msg = xchg(&psock->bpf_tx_msg, tx_msg);
	if (orig_tx_msg)
		bpf_prog_put(orig_tx_msg);
}