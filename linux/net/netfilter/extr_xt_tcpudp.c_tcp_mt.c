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
struct xt_tcp {int invflags; unsigned char flg_mask; unsigned char flg_cmp; scalar_t__ option; int /*<<< orphan*/ * dpts; int /*<<< orphan*/ * spts; } ;
struct xt_action_param {int fragoff; int hotdrop; int /*<<< orphan*/  thoff; struct xt_tcp* matchinfo; } ;
struct tcphdr {int doff; int /*<<< orphan*/  dest; int /*<<< orphan*/  source; } ;
struct sk_buff {int dummy; } ;
typedef  int /*<<< orphan*/  _tcph ;

/* Variables and functions */
 int /*<<< orphan*/  NF_INVF (struct xt_tcp const*,int /*<<< orphan*/ ,int) ; 
 int XT_TCP_INV_DSTPT ; 
 int /*<<< orphan*/  XT_TCP_INV_FLAGS ; 
 int XT_TCP_INV_OPTION ; 
 int XT_TCP_INV_SRCPT ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  port_match (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 struct tcphdr* skb_header_pointer (struct sk_buff const*,int /*<<< orphan*/ ,int,struct tcphdr*) ; 
 int /*<<< orphan*/  tcp_find_option (scalar_t__,struct sk_buff const*,int /*<<< orphan*/ ,int,int,int*) ; 

__attribute__((used)) static bool tcp_mt(const struct sk_buff *skb, struct xt_action_param *par)
{
	const struct tcphdr *th;
	struct tcphdr _tcph;
	const struct xt_tcp *tcpinfo = par->matchinfo;

	if (par->fragoff != 0) {
		/* To quote Alan:

		   Don't allow a fragment of TCP 8 bytes in. Nobody normal
		   causes this. Its a cracker trying to break in by doing a
		   flag overwrite to pass the direction checks.
		*/
		if (par->fragoff == 1) {
			pr_debug("Dropping evil TCP offset=1 frag.\n");
			par->hotdrop = true;
		}
		/* Must not be a fragment. */
		return false;
	}

	th = skb_header_pointer(skb, par->thoff, sizeof(_tcph), &_tcph);
	if (th == NULL) {
		/* We've been asked to examine this packet, and we
		   can't.  Hence, no choice but to drop. */
		pr_debug("Dropping evil TCP offset=0 tinygram.\n");
		par->hotdrop = true;
		return false;
	}

	if (!port_match(tcpinfo->spts[0], tcpinfo->spts[1],
			ntohs(th->source),
			!!(tcpinfo->invflags & XT_TCP_INV_SRCPT)))
		return false;
	if (!port_match(tcpinfo->dpts[0], tcpinfo->dpts[1],
			ntohs(th->dest),
			!!(tcpinfo->invflags & XT_TCP_INV_DSTPT)))
		return false;
	if (!NF_INVF(tcpinfo, XT_TCP_INV_FLAGS,
		     (((unsigned char *)th)[13] & tcpinfo->flg_mask) == tcpinfo->flg_cmp))
		return false;
	if (tcpinfo->option) {
		if (th->doff * 4 < sizeof(_tcph)) {
			par->hotdrop = true;
			return false;
		}
		if (!tcp_find_option(tcpinfo->option, skb, par->thoff,
				     th->doff*4 - sizeof(_tcph),
				     tcpinfo->invflags & XT_TCP_INV_OPTION,
				     &par->hotdrop))
			return false;
	}
	return true;
}