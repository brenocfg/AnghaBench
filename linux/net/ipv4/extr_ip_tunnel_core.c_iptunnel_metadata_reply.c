#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct TYPE_7__ {int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct TYPE_9__ {TYPE_3__ ipv4; TYPE_2__ ipv6; } ;
struct TYPE_10__ {int /*<<< orphan*/  tun_flags; TYPE_4__ u; int /*<<< orphan*/  tun_id; } ;
struct ip_tunnel_info {int mode; TYPE_5__ key; } ;
struct TYPE_6__ {struct ip_tunnel_info tun_info; } ;
struct metadata_dst {scalar_t__ type; TYPE_1__ u; } ;
struct in6_addr {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int IP_TUNNEL_INFO_IPV6 ; 
 int IP_TUNNEL_INFO_TX ; 
 scalar_t__ METADATA_IP_TUNNEL ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct metadata_dst* metadata_dst_alloc (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

struct metadata_dst *iptunnel_metadata_reply(struct metadata_dst *md,
					     gfp_t flags)
{
	struct metadata_dst *res;
	struct ip_tunnel_info *dst, *src;

	if (!md || md->type != METADATA_IP_TUNNEL ||
	    md->u.tun_info.mode & IP_TUNNEL_INFO_TX)

		return NULL;

	res = metadata_dst_alloc(0, METADATA_IP_TUNNEL, flags);
	if (!res)
		return NULL;

	dst = &res->u.tun_info;
	src = &md->u.tun_info;
	dst->key.tun_id = src->key.tun_id;
	if (src->mode & IP_TUNNEL_INFO_IPV6)
		memcpy(&dst->key.u.ipv6.dst, &src->key.u.ipv6.src,
		       sizeof(struct in6_addr));
	else
		dst->key.u.ipv4.dst = src->key.u.ipv4.src;
	dst->key.tun_flags = src->key.tun_flags;
	dst->mode = src->mode | IP_TUNNEL_INFO_TX;

	return res;
}