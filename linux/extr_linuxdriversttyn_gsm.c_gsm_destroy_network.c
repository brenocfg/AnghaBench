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
struct gsm_mux_net {int dummy; } ;
struct gsm_dlci {int /*<<< orphan*/  net; } ;

/* Variables and functions */
 int /*<<< orphan*/  muxnet_put (struct gsm_mux_net*) ; 
 struct gsm_mux_net* netdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static void gsm_destroy_network(struct gsm_dlci *dlci)
{
	struct gsm_mux_net *mux_net;

	pr_debug("destroy network interface");
	if (!dlci->net)
		return;
	mux_net = netdev_priv(dlci->net);
	muxnet_put(mux_net);
}