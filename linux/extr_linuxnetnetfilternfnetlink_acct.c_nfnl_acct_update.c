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
struct sk_buff {int /*<<< orphan*/  len; } ;
struct nf_acct {int /*<<< orphan*/  bytes; int /*<<< orphan*/  pkts; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic64_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic64_inc (int /*<<< orphan*/ *) ; 

void nfnl_acct_update(const struct sk_buff *skb, struct nf_acct *nfacct)
{
	atomic64_inc(&nfacct->pkts);
	atomic64_add(skb->len, &nfacct->bytes);
}