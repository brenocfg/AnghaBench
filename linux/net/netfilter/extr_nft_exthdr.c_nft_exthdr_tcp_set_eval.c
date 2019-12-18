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
typedef  scalar_t__ u8 ;
typedef  void* u32 ;
typedef  void* u16 ;
struct tcphdr {int /*<<< orphan*/  check; } ;
struct nft_regs {void** data; } ;
struct TYPE_2__ {scalar_t__ thoff; } ;
struct nft_pktinfo {int /*<<< orphan*/  skb; TYPE_1__ xt; } ;
struct nft_exthdr {scalar_t__ type; unsigned int len; unsigned int offset; size_t sreg; } ;
struct nft_expr {int dummy; } ;
typedef  int /*<<< orphan*/  buff ;
typedef  void* __be32 ;
typedef  void* __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_TCP_OPTION_SPACE ; 
#define  TCPOPT_MSS 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 void* get_unaligned (void**) ; 
 int /*<<< orphan*/  inet_proto_csum_replace2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,void*,int) ; 
 int /*<<< orphan*/  inet_proto_csum_replace4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,void*,int) ; 
 struct nft_exthdr* nft_expr_priv (struct nft_expr const*) ; 
 struct tcphdr* nft_tcp_header_pointer (struct nft_pktinfo const*,int,scalar_t__*,unsigned int*) ; 
 int /*<<< orphan*/  ntohs (void*) ; 
 unsigned int optlen (scalar_t__*,unsigned int) ; 
 int /*<<< orphan*/  put_unaligned (void*,void**) ; 
 scalar_t__ skb_ensure_writable (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void nft_exthdr_tcp_set_eval(const struct nft_expr *expr,
				    struct nft_regs *regs,
				    const struct nft_pktinfo *pkt)
{
	u8 buff[sizeof(struct tcphdr) + MAX_TCP_OPTION_SPACE];
	struct nft_exthdr *priv = nft_expr_priv(expr);
	unsigned int i, optl, tcphdr_len, offset;
	struct tcphdr *tcph;
	u8 *opt;
	u32 src;

	tcph = nft_tcp_header_pointer(pkt, sizeof(buff), buff, &tcphdr_len);
	if (!tcph)
		return;

	opt = (u8 *)tcph;
	for (i = sizeof(*tcph); i < tcphdr_len - 1; i += optl) {
		union {
			u8 octet;
			__be16 v16;
			__be32 v32;
		} old, new;

		optl = optlen(opt, i);

		if (priv->type != opt[i])
			continue;

		if (i + optl > tcphdr_len || priv->len + priv->offset > optl)
			return;

		if (skb_ensure_writable(pkt->skb,
					pkt->xt.thoff + i + priv->len))
			return;

		tcph = nft_tcp_header_pointer(pkt, sizeof(buff), buff,
					      &tcphdr_len);
		if (!tcph)
			return;

		src = regs->data[priv->sreg];
		offset = i + priv->offset;

		switch (priv->len) {
		case 2:
			old.v16 = get_unaligned((u16 *)(opt + offset));
			new.v16 = src;

			switch (priv->type) {
			case TCPOPT_MSS:
				/* increase can cause connection to stall */
				if (ntohs(old.v16) <= ntohs(new.v16))
					return;
			break;
			}

			if (old.v16 == new.v16)
				return;

			put_unaligned(new.v16, (u16*)(opt + offset));
			inet_proto_csum_replace2(&tcph->check, pkt->skb,
						 old.v16, new.v16, false);
			break;
		case 4:
			new.v32 = src;
			old.v32 = get_unaligned((u32 *)(opt + offset));

			if (old.v32 == new.v32)
				return;

			put_unaligned(new.v32, (u32*)(opt + offset));
			inet_proto_csum_replace4(&tcph->check, pkt->skb,
						 old.v32, new.v32, false);
			break;
		default:
			WARN_ON_ONCE(1);
			break;
		}

		return;
	}
}