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
struct ip_tunnel_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ip_tunnel_info*) ; 

__attribute__((used)) static void tcf_tunnel_encap_put_tunnel(void *priv)
{
	struct ip_tunnel_info *tunnel = priv;

	kfree(tunnel);
}