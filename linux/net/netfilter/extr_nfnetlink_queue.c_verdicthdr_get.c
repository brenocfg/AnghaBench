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
struct nlattr {int dummy; } ;
struct nfqnl_msg_verdict_hdr {int /*<<< orphan*/  verdict; } ;

/* Variables and functions */
 size_t NFQA_VERDICT_HDR ; 
 unsigned int NF_MAX_VERDICT ; 
 unsigned int NF_STOLEN ; 
 unsigned int NF_VERDICT_MASK ; 
 struct nfqnl_msg_verdict_hdr* nla_data (struct nlattr const* const) ; 
 unsigned int ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nfqnl_msg_verdict_hdr*
verdicthdr_get(const struct nlattr * const nfqa[])
{
	struct nfqnl_msg_verdict_hdr *vhdr;
	unsigned int verdict;

	if (!nfqa[NFQA_VERDICT_HDR])
		return NULL;

	vhdr = nla_data(nfqa[NFQA_VERDICT_HDR]);
	verdict = ntohl(vhdr->verdict) & NF_VERDICT_MASK;
	if (verdict > NF_MAX_VERDICT || verdict == NF_STOLEN)
		return NULL;
	return vhdr;
}