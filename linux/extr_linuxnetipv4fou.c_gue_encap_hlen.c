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
struct udphdr {int dummy; } ;
struct ip_tunnel_encap {int flags; } ;
struct guehdr {int dummy; } ;

/* Variables and functions */
 size_t GUE_LEN_PRIV ; 
 scalar_t__ GUE_PLEN_REMCSUM ; 
 int TUNNEL_ENCAP_FLAG_REMCSUM ; 

size_t gue_encap_hlen(struct ip_tunnel_encap *e)
{
	size_t len;
	bool need_priv = false;

	len = sizeof(struct udphdr) + sizeof(struct guehdr);

	if (e->flags & TUNNEL_ENCAP_FLAG_REMCSUM) {
		len += GUE_PLEN_REMCSUM;
		need_priv = true;
	}

	len += need_priv ? GUE_LEN_PRIV : 0;

	return len;
}