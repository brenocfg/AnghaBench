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
typedef  int u32 ;
struct tcphdr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  code; } ;
struct nft_regs {int* data; TYPE_1__ verdict; } ;
struct nft_pktinfo {int dummy; } ;
struct nft_exthdr {size_t dreg; scalar_t__ type; unsigned int len; unsigned int offset; int flags; } ;
struct nft_expr {int dummy; } ;
typedef  int /*<<< orphan*/  buff ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_TCP_OPTION_SPACE ; 
 int /*<<< orphan*/  NFT_BREAK ; 
 int NFT_EXTHDR_F_PRESENT ; 
 size_t NFT_REG32_SIZE ; 
 int /*<<< orphan*/  memcpy (int*,scalar_t__*,size_t) ; 
 struct nft_exthdr* nft_expr_priv (struct nft_expr const*) ; 
 struct tcphdr* nft_tcp_header_pointer (struct nft_pktinfo const*,int,scalar_t__*,unsigned int*) ; 
 unsigned int optlen (scalar_t__*,unsigned int) ; 

__attribute__((used)) static void nft_exthdr_tcp_eval(const struct nft_expr *expr,
				struct nft_regs *regs,
				const struct nft_pktinfo *pkt)
{
	u8 buff[sizeof(struct tcphdr) + MAX_TCP_OPTION_SPACE];
	struct nft_exthdr *priv = nft_expr_priv(expr);
	unsigned int i, optl, tcphdr_len, offset;
	u32 *dest = &regs->data[priv->dreg];
	struct tcphdr *tcph;
	u8 *opt;

	tcph = nft_tcp_header_pointer(pkt, sizeof(buff), buff, &tcphdr_len);
	if (!tcph)
		goto err;

	opt = (u8 *)tcph;
	for (i = sizeof(*tcph); i < tcphdr_len - 1; i += optl) {
		optl = optlen(opt, i);

		if (priv->type != opt[i])
			continue;

		if (i + optl > tcphdr_len || priv->len + priv->offset > optl)
			goto err;

		offset = i + priv->offset;
		if (priv->flags & NFT_EXTHDR_F_PRESENT) {
			*dest = 1;
		} else {
			dest[priv->len / NFT_REG32_SIZE] = 0;
			memcpy(dest, opt + offset, priv->len);
		}

		return;
	}

err:
	if (priv->flags & NFT_EXTHDR_F_PRESENT)
		*dest = 0;
	else
		regs->verdict.code = NFT_BREAK;
}