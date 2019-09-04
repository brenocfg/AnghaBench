#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  elp_interval; int /*<<< orphan*/  throughput_override; } ;
struct batadv_hard_iface {TYPE_1__ bat_v; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 

void batadv_v_hardif_init(struct batadv_hard_iface *hard_iface)
{
	/* enable link throughput auto-detection by setting the throughput
	 * override to zero
	 */
	atomic_set(&hard_iface->bat_v.throughput_override, 0);
	atomic_set(&hard_iface->bat_v.elp_interval, 500);
}