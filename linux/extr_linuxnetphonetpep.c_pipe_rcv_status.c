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
struct sock {int /*<<< orphan*/  (* sk_write_space ) (struct sock*) ;} ;
struct sk_buff {int dummy; } ;
struct pnpipehdr {scalar_t__ pep_type; int* data; } ;
struct pep_sock {int /*<<< orphan*/  tx_credits; int /*<<< orphan*/  tx_fc; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
#define  PEP_IND_BUSY 133 
#define  PEP_IND_READY 132 
#define  PN_LEGACY_FLOW_CONTROL 131 
 int /*<<< orphan*/  PN_MULTI_CREDIT_FLOW_CONTROL ; 
#define  PN_ONE_CREDIT_FLOW_CONTROL 130 
#define  PN_PEP_IND_FLOW_CONTROL 129 
#define  PN_PEP_IND_ID_MCFC_GRANT_CREDITS 128 
 scalar_t__ PN_PEP_TYPE_COMMON ; 
 int /*<<< orphan*/  atomic_add (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  net_dbg_ratelimited (char*,unsigned int) ; 
 struct pep_sock* pep_sk (struct sock*) ; 
 struct pnpipehdr* pnp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

__attribute__((used)) static int pipe_rcv_status(struct sock *sk, struct sk_buff *skb)
{
	struct pep_sock *pn = pep_sk(sk);
	struct pnpipehdr *hdr;
	int wake = 0;

	if (!pskb_may_pull(skb, sizeof(*hdr) + 4))
		return -EINVAL;

	hdr = pnp_hdr(skb);
	if (hdr->pep_type != PN_PEP_TYPE_COMMON) {
		net_dbg_ratelimited("Phonet unknown PEP type: %u\n",
				    (unsigned int)hdr->pep_type);
		return -EOPNOTSUPP;
	}

	switch (hdr->data[0]) {
	case PN_PEP_IND_FLOW_CONTROL:
		switch (pn->tx_fc) {
		case PN_LEGACY_FLOW_CONTROL:
			switch (hdr->data[3]) {
			case PEP_IND_BUSY:
				atomic_set(&pn->tx_credits, 0);
				break;
			case PEP_IND_READY:
				atomic_set(&pn->tx_credits, wake = 1);
				break;
			}
			break;
		case PN_ONE_CREDIT_FLOW_CONTROL:
			if (hdr->data[3] == PEP_IND_READY)
				atomic_set(&pn->tx_credits, wake = 1);
			break;
		}
		break;

	case PN_PEP_IND_ID_MCFC_GRANT_CREDITS:
		if (pn->tx_fc != PN_MULTI_CREDIT_FLOW_CONTROL)
			break;
		atomic_add(wake = hdr->data[3], &pn->tx_credits);
		break;

	default:
		net_dbg_ratelimited("Phonet unknown PEP indication: %u\n",
				    (unsigned int)hdr->data[0]);
		return -EOPNOTSUPP;
	}
	if (wake)
		sk->sk_write_space(sk);
	return 0;
}