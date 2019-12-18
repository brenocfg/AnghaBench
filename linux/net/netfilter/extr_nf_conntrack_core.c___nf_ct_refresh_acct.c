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
typedef  scalar_t__ u32 ;
struct sk_buff {int /*<<< orphan*/  len; } ;
struct nf_conn {int /*<<< orphan*/  timeout; int /*<<< orphan*/  status; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;

/* Variables and functions */
 int /*<<< orphan*/  IPS_FIXED_TIMEOUT_BIT ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  nf_ct_acct_update (struct nf_conn*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ nf_ct_is_confirmed (struct nf_conn*) ; 
 scalar_t__ nfct_time_stamp ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void __nf_ct_refresh_acct(struct nf_conn *ct,
			  enum ip_conntrack_info ctinfo,
			  const struct sk_buff *skb,
			  u32 extra_jiffies,
			  bool do_acct)
{
	/* Only update if this is not a fixed timeout */
	if (test_bit(IPS_FIXED_TIMEOUT_BIT, &ct->status))
		goto acct;

	/* If not in hash table, timer will not be active yet */
	if (nf_ct_is_confirmed(ct))
		extra_jiffies += nfct_time_stamp;

	if (READ_ONCE(ct->timeout) != extra_jiffies)
		WRITE_ONCE(ct->timeout, extra_jiffies);
acct:
	if (do_acct)
		nf_ct_acct_update(ct, ctinfo, skb->len);
}