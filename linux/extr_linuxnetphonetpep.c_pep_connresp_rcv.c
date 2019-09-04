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
typedef  scalar_t__ u8 ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct pnpipehdr {scalar_t__ error_code; scalar_t__* data; } ;
struct pep_sock {void* rx_fc; void* tx_fc; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int ECONNREFUSED ; 
 int EINVAL ; 
 scalar_t__ PN_PIPE_NO_ERROR ; 
#define  PN_PIPE_SB_PREFERRED_FC_RX 129 
#define  PN_PIPE_SB_REQUIRED_FC_TX 128 
 scalar_t__* pep_get_sb (struct sk_buff*,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 struct pep_sock* pep_sk (struct sock*) ; 
 int pipe_handler_send_created_ind (struct sock*) ; 
 void* pipe_negotiate_fc (scalar_t__ const*,int /*<<< orphan*/ ) ; 
 struct pnpipehdr* pnp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  pskb_pull (struct sk_buff*,int) ; 

__attribute__((used)) static int pep_connresp_rcv(struct sock *sk, struct sk_buff *skb)
{
	struct pep_sock *pn = pep_sk(sk);
	struct pnpipehdr *hdr;
	u8 n_sb;

	if (!pskb_pull(skb, sizeof(*hdr) + 4))
		return -EINVAL;

	hdr = pnp_hdr(skb);
	if (hdr->error_code != PN_PIPE_NO_ERROR)
		return -ECONNREFUSED;

	/* Parse sub-blocks */
	n_sb = hdr->data[3];
	while (n_sb > 0) {
		u8 type, buf[6], len = sizeof(buf);
		const u8 *data = pep_get_sb(skb, &type, &len, buf);

		if (data == NULL)
			return -EINVAL;

		switch (type) {
		case PN_PIPE_SB_REQUIRED_FC_TX:
			if (len < 2 || len < data[0])
				break;
			pn->tx_fc = pipe_negotiate_fc(data + 2, len - 2);
			break;

		case PN_PIPE_SB_PREFERRED_FC_RX:
			if (len < 2 || len < data[0])
				break;
			pn->rx_fc = pipe_negotiate_fc(data + 2, len - 2);
			break;

		}
		n_sb--;
	}

	return pipe_handler_send_created_ind(sk);
}