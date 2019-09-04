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
struct xenvif {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  xen_unregister_credit_watch (struct xenvif*) ; 
 int /*<<< orphan*/  xen_unregister_mcast_ctrl_watch (struct xenvif*) ; 

__attribute__((used)) static void xen_unregister_watchers(struct xenvif *vif)
{
	xen_unregister_mcast_ctrl_watch(vif);
	xen_unregister_credit_watch(vif);
}