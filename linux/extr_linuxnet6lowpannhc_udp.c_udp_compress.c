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
typedef  int u8 ;
typedef  int /*<<< orphan*/  tmp ;
struct udphdr {int source; int dest; int check; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int LOWPAN_NHC_UDP_4BIT_MASK ; 
 int LOWPAN_NHC_UDP_4BIT_PORT ; 
 int LOWPAN_NHC_UDP_8BIT_MASK ; 
 int LOWPAN_NHC_UDP_8BIT_PORT ; 
 int LOWPAN_NHC_UDP_CS_P_00 ; 
 int LOWPAN_NHC_UDP_CS_P_01 ; 
 int LOWPAN_NHC_UDP_CS_P_10 ; 
 int LOWPAN_NHC_UDP_CS_P_11 ; 
 int /*<<< orphan*/  lowpan_push_hc_data (int**,int*,int) ; 
 int ntohs (int) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 struct udphdr* udp_hdr (struct sk_buff*) ; 

__attribute__((used)) static int udp_compress(struct sk_buff *skb, u8 **hc_ptr)
{
	const struct udphdr *uh = udp_hdr(skb);
	u8 tmp;

	if (((ntohs(uh->source) & LOWPAN_NHC_UDP_4BIT_MASK) ==
	     LOWPAN_NHC_UDP_4BIT_PORT) &&
	    ((ntohs(uh->dest) & LOWPAN_NHC_UDP_4BIT_MASK) ==
	     LOWPAN_NHC_UDP_4BIT_PORT)) {
		pr_debug("UDP header: both ports compression to 4 bits\n");
		/* compression value */
		tmp = LOWPAN_NHC_UDP_CS_P_11;
		lowpan_push_hc_data(hc_ptr, &tmp, sizeof(tmp));
		/* source and destination port */
		tmp = ntohs(uh->dest) - LOWPAN_NHC_UDP_4BIT_PORT +
		      ((ntohs(uh->source) - LOWPAN_NHC_UDP_4BIT_PORT) << 4);
		lowpan_push_hc_data(hc_ptr, &tmp, sizeof(tmp));
	} else if ((ntohs(uh->dest) & LOWPAN_NHC_UDP_8BIT_MASK) ==
			LOWPAN_NHC_UDP_8BIT_PORT) {
		pr_debug("UDP header: remove 8 bits of dest\n");
		/* compression value */
		tmp = LOWPAN_NHC_UDP_CS_P_01;
		lowpan_push_hc_data(hc_ptr, &tmp, sizeof(tmp));
		/* source port */
		lowpan_push_hc_data(hc_ptr, &uh->source, sizeof(uh->source));
		/* destination port */
		tmp = ntohs(uh->dest) - LOWPAN_NHC_UDP_8BIT_PORT;
		lowpan_push_hc_data(hc_ptr, &tmp, sizeof(tmp));
	} else if ((ntohs(uh->source) & LOWPAN_NHC_UDP_8BIT_MASK) ==
			LOWPAN_NHC_UDP_8BIT_PORT) {
		pr_debug("UDP header: remove 8 bits of source\n");
		/* compression value */
		tmp = LOWPAN_NHC_UDP_CS_P_10;
		lowpan_push_hc_data(hc_ptr, &tmp, sizeof(tmp));
		/* source port */
		tmp = ntohs(uh->source) - LOWPAN_NHC_UDP_8BIT_PORT;
		lowpan_push_hc_data(hc_ptr, &tmp, sizeof(tmp));
		/* destination port */
		lowpan_push_hc_data(hc_ptr, &uh->dest, sizeof(uh->dest));
	} else {
		pr_debug("UDP header: can't compress\n");
		/* compression value */
		tmp = LOWPAN_NHC_UDP_CS_P_00;
		lowpan_push_hc_data(hc_ptr, &tmp, sizeof(tmp));
		/* source port */
		lowpan_push_hc_data(hc_ptr, &uh->source, sizeof(uh->source));
		/* destination port */
		lowpan_push_hc_data(hc_ptr, &uh->dest, sizeof(uh->dest));
	}

	/* checksum is always inline */
	lowpan_push_hc_data(hc_ptr, &uh->check, sizeof(uh->check));

	return 0;
}