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
struct seg6_iptunnel_encap {int dummy; } ;
struct lwtunnel_state {int dummy; } ;

/* Variables and functions */
 int SEG6_IPTUN_ENCAP_SIZE (struct seg6_iptunnel_encap*) ; 
 int memcmp (struct seg6_iptunnel_encap*,struct seg6_iptunnel_encap*,int) ; 
 struct seg6_iptunnel_encap* seg6_encap_lwtunnel (struct lwtunnel_state*) ; 

__attribute__((used)) static int seg6_encap_cmp(struct lwtunnel_state *a, struct lwtunnel_state *b)
{
	struct seg6_iptunnel_encap *a_hdr = seg6_encap_lwtunnel(a);
	struct seg6_iptunnel_encap *b_hdr = seg6_encap_lwtunnel(b);
	int len = SEG6_IPTUN_ENCAP_SIZE(a_hdr);

	if (len != SEG6_IPTUN_ENCAP_SIZE(b_hdr))
		return 1;

	return memcmp(a_hdr, b_hdr, len);
}