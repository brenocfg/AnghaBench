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
struct nft_regs {int dummy; } ;
struct nft_pktinfo {TYPE_1__* skb; } ;
struct nft_counter_percpu_priv {int /*<<< orphan*/ * counter; } ;
struct nft_counter {int /*<<< orphan*/  packets; int /*<<< orphan*/  bytes; } ;
typedef  int /*<<< orphan*/  seqcount_t ;
struct TYPE_2__ {scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  nft_counter_seq ; 
 void* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_seqcount_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_seqcount_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void nft_counter_do_eval(struct nft_counter_percpu_priv *priv,
				       struct nft_regs *regs,
				       const struct nft_pktinfo *pkt)
{
	struct nft_counter *this_cpu;
	seqcount_t *myseq;

	local_bh_disable();
	this_cpu = this_cpu_ptr(priv->counter);
	myseq = this_cpu_ptr(&nft_counter_seq);

	write_seqcount_begin(myseq);

	this_cpu->bytes += pkt->skb->len;
	this_cpu->packets++;

	write_seqcount_end(myseq);
	local_bh_enable();
}