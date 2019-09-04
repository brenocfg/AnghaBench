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
struct rpc_xprt_switch {int /*<<< orphan*/  xps_kref; } ;

/* Variables and functions */
 scalar_t__ kref_get_unless_zero (int /*<<< orphan*/ *) ; 

struct rpc_xprt_switch *xprt_switch_get(struct rpc_xprt_switch *xps)
{
	if (xps != NULL && kref_get_unless_zero(&xps->xps_kref))
		return xps;
	return NULL;
}