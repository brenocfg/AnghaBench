#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct nft_traceinfo {scalar_t__ type; TYPE_2__* rule; TYPE_1__* verdict; } ;
struct TYPE_4__ {int /*<<< orphan*/  handle; } ;
struct TYPE_3__ {scalar_t__ code; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFTA_TRACE_PAD ; 
 int /*<<< orphan*/  NFTA_TRACE_RULE_HANDLE ; 
 scalar_t__ NFT_CONTINUE ; 
 scalar_t__ NFT_TRACETYPE_RETURN ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int nla_put_be64 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nf_trace_fill_rule_info(struct sk_buff *nlskb,
				   const struct nft_traceinfo *info)
{
	if (!info->rule)
		return 0;

	/* a continue verdict with ->type == RETURN means that this is
	 * an implicit return (end of chain reached).
	 *
	 * Since no rule matched, the ->rule pointer is invalid.
	 */
	if (info->type == NFT_TRACETYPE_RETURN &&
	    info->verdict->code == NFT_CONTINUE)
		return 0;

	return nla_put_be64(nlskb, NFTA_TRACE_RULE_HANDLE,
			    cpu_to_be64(info->rule->handle),
			    NFTA_TRACE_PAD);
}