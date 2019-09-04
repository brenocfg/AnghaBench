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
struct seg6_local_lwt {struct ipv6_sr_hdr* srh; } ;
struct nlattr {int dummy; } ;
struct ipv6_sr_hdr {int hdrlen; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  SEG6_LOCAL_SRH ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct ipv6_sr_hdr*,int) ; 
 int /*<<< orphan*/  nla_data (struct nlattr*) ; 
 struct nlattr* nla_reserve (struct sk_buff*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int put_nla_srh(struct sk_buff *skb, struct seg6_local_lwt *slwt)
{
	struct ipv6_sr_hdr *srh;
	struct nlattr *nla;
	int len;

	srh = slwt->srh;
	len = (srh->hdrlen + 1) << 3;

	nla = nla_reserve(skb, SEG6_LOCAL_SRH, len);
	if (!nla)
		return -EMSGSIZE;

	memcpy(nla_data(nla), srh, len);

	return 0;
}