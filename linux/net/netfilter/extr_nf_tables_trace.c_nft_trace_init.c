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
struct nft_verdict {int dummy; } ;
struct nft_traceinfo {int trace; int packet_dumped; struct nft_verdict const* verdict; struct nft_pktinfo const* pkt; int /*<<< orphan*/  basechain; } ;
struct nft_pktinfo {int dummy; } ;
struct nft_chain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nft_base_chain (struct nft_chain const*) ; 

void nft_trace_init(struct nft_traceinfo *info, const struct nft_pktinfo *pkt,
		    const struct nft_verdict *verdict,
		    const struct nft_chain *chain)
{
	info->basechain = nft_base_chain(chain);
	info->trace = true;
	info->packet_dumped = false;
	info->pkt = pkt;
	info->verdict = verdict;
}