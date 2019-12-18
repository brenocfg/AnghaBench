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
struct TYPE_2__ {int /*<<< orphan*/  metric_work; int /*<<< orphan*/  throughput; } ;
struct batadv_hardif_neigh_node {TYPE_1__ bat_v; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_v_elp_throughput_metric_update ; 
 int /*<<< orphan*/  ewma_throughput_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
batadv_v_hardif_neigh_init(struct batadv_hardif_neigh_node *hardif_neigh)
{
	ewma_throughput_init(&hardif_neigh->bat_v.throughput);
	INIT_WORK(&hardif_neigh->bat_v.metric_work,
		  batadv_v_elp_throughput_metric_update);
}