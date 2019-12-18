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
struct ip_tunnel_info {int /*<<< orphan*/  dst_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  dst_cache_destroy (int /*<<< orphan*/ *) ; 
 struct ip_tunnel_info* lwt_tun_info (struct lwtunnel_state*) ; 

__attribute__((used)) static void ip_tun_destroy_state(struct lwtunnel_state *lwtstate)
{
#ifdef CONFIG_DST_CACHE
	struct ip_tunnel_info *tun_info = lwt_tun_info(lwtstate);

	dst_cache_destroy(&tun_info->dst_cache);
#endif
}