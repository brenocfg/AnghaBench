#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ daddr; } ;
struct ip_tunnel_parm {int i_flags; TYPE_1__ iph; scalar_t__ i_key; } ;
struct ip_tunnel_net {struct hlist_head* tunnels; } ;
struct hlist_head {int dummy; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int TUNNEL_KEY ; 
 int VTI_ISVTI ; 
 unsigned int ip_tunnel_hash (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ipv4_is_multicast (scalar_t__) ; 

__attribute__((used)) static struct hlist_head *ip_bucket(struct ip_tunnel_net *itn,
				    struct ip_tunnel_parm *parms)
{
	unsigned int h;
	__be32 remote;
	__be32 i_key = parms->i_key;

	if (parms->iph.daddr && !ipv4_is_multicast(parms->iph.daddr))
		remote = parms->iph.daddr;
	else
		remote = 0;

	if (!(parms->i_flags & TUNNEL_KEY) && (parms->i_flags & VTI_ISVTI))
		i_key = 0;

	h = ip_tunnel_hash(i_key, remote);
	return &itn->tunnels[h];
}