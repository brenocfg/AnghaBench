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
struct batadv_hard_iface {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  batadv_iv_ogm_schedule (struct batadv_hard_iface*) ; 

__attribute__((used)) static void batadv_iv_iface_enabled(struct batadv_hard_iface *hard_iface)
{
	/* begin scheduling originator messages on that interface */
	batadv_iv_ogm_schedule(hard_iface);
}