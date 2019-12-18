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
struct lwtunnel_state {int dummy; } ;
struct ip_tunnel_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lwt_tun_info (struct lwtunnel_state*) ; 
 int memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ip_tun_cmp_encap(struct lwtunnel_state *a, struct lwtunnel_state *b)
{
	return memcmp(lwt_tun_info(a), lwt_tun_info(b),
		      sizeof(struct ip_tunnel_info));
}