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
struct ip_tunnel_encap_ops {int dummy; } ;

/* Variables and functions */
 int ERANGE ; 
 unsigned int MAX_IPTUN_ENCAP_OPS ; 
 int /*<<< orphan*/  cmpxchg (struct ip_tunnel_encap_ops const**,int /*<<< orphan*/ *,struct ip_tunnel_encap_ops const*) ; 
 int /*<<< orphan*/ * iptun_encaps ; 

int ip_tunnel_encap_add_ops(const struct ip_tunnel_encap_ops *ops,
			    unsigned int num)
{
	if (num >= MAX_IPTUN_ENCAP_OPS)
		return -ERANGE;

	return !cmpxchg((const struct ip_tunnel_encap_ops **)
			&iptun_encaps[num],
			NULL, ops) ? 0 : -1;
}