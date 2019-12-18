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
struct sk_buff {int dummy; } ;
struct net_device {int /*<<< orphan*/  type; int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFTA_TRACE_IIF ; 
 int /*<<< orphan*/  NFTA_TRACE_IIFTYPE ; 
 int /*<<< orphan*/  NFTA_TRACE_OIF ; 
 int /*<<< orphan*/  NFTA_TRACE_OIFTYPE ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_be16 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_be32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nf_trace_fill_dev_info(struct sk_buff *nlskb,
				  const struct net_device *indev,
				  const struct net_device *outdev)
{
	if (indev) {
		if (nla_put_be32(nlskb, NFTA_TRACE_IIF,
				 htonl(indev->ifindex)))
			return -1;

		if (nla_put_be16(nlskb, NFTA_TRACE_IIFTYPE,
				 htons(indev->type)))
			return -1;
	}

	if (outdev) {
		if (nla_put_be32(nlskb, NFTA_TRACE_OIF,
				 htonl(outdev->ifindex)))
			return -1;

		if (nla_put_be16(nlskb, NFTA_TRACE_OIFTYPE,
				 htons(outdev->type)))
			return -1;
	}

	return 0;
}