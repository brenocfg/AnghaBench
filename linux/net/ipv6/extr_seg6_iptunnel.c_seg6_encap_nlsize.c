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
 int /*<<< orphan*/  SEG6_IPTUN_ENCAP_SIZE (struct seg6_iptunnel_encap*) ; 
 int nla_total_size (int /*<<< orphan*/ ) ; 
 struct seg6_iptunnel_encap* seg6_encap_lwtunnel (struct lwtunnel_state*) ; 

__attribute__((used)) static int seg6_encap_nlsize(struct lwtunnel_state *lwtstate)
{
	struct seg6_iptunnel_encap *tuninfo = seg6_encap_lwtunnel(lwtstate);

	return nla_total_size(SEG6_IPTUN_ENCAP_SIZE(tuninfo));
}