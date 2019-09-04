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
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct pdp_ctx {int dummy; } ;

/* Variables and functions */
#define  ETH_P_IP 128 
 int gtp_check_ms_ipv4 (struct sk_buff*,struct pdp_ctx*,unsigned int,unsigned int) ; 
 int ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool gtp_check_ms(struct sk_buff *skb, struct pdp_ctx *pctx,
			     unsigned int hdrlen, unsigned int role)
{
	switch (ntohs(skb->protocol)) {
	case ETH_P_IP:
		return gtp_check_ms_ipv4(skb, pctx, hdrlen, role);
	}
	return false;
}