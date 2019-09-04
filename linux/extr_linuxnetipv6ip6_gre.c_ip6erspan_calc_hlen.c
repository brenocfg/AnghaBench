#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ipv6hdr {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  erspan_ver; } ;
struct ip6_tnl {int tun_hlen; int hlen; int encap_hlen; TYPE_2__* dev; TYPE_1__ parms; } ;
struct TYPE_4__ {scalar_t__ needed_headroom; } ;

/* Variables and functions */
 scalar_t__ LL_MAX_HEADER ; 
 int erspan_hdr_len (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ip6erspan_calc_hlen(struct ip6_tnl *tunnel)
{
	int t_hlen;

	tunnel->tun_hlen = 8;
	tunnel->hlen = tunnel->tun_hlen + tunnel->encap_hlen +
		       erspan_hdr_len(tunnel->parms.erspan_ver);

	t_hlen = tunnel->hlen + sizeof(struct ipv6hdr);
	tunnel->dev->needed_headroom = LL_MAX_HEADER + t_hlen;
	return t_hlen;
}