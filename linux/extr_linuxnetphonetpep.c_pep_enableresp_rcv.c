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
struct sk_buff {int dummy; } ;
struct pnpipehdr {scalar_t__ error_code; } ;

/* Variables and functions */
 int ECONNREFUSED ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  PNS_PIPE_ENABLED_IND ; 
 scalar_t__ PN_PIPE_NO_ERROR ; 
 int pep_indicate (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pnpipehdr* pnp_hdr (struct sk_buff*) ; 

__attribute__((used)) static int pep_enableresp_rcv(struct sock *sk, struct sk_buff *skb)
{
	struct pnpipehdr *hdr = pnp_hdr(skb);

	if (hdr->error_code != PN_PIPE_NO_ERROR)
		return -ECONNREFUSED;

	return pep_indicate(sk, PNS_PIPE_ENABLED_IND, 0 /* sub-blocks */,
		NULL, 0, GFP_ATOMIC);

}