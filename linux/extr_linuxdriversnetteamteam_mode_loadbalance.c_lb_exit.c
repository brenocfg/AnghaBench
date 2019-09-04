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
struct team {int dummy; } ;
struct lb_priv {TYPE_2__* ex; int /*<<< orphan*/  pcpu_stats; } ;
struct TYPE_3__ {int /*<<< orphan*/  refresh_dw; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 
 struct lb_priv* get_lb_priv (struct team*) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 int /*<<< orphan*/  lb_bpf_func_free (struct team*) ; 
 int /*<<< orphan*/  lb_options ; 
 int /*<<< orphan*/  team_options_unregister (struct team*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lb_exit(struct team *team)
{
	struct lb_priv *lb_priv = get_lb_priv(team);

	team_options_unregister(team, lb_options,
				ARRAY_SIZE(lb_options));
	lb_bpf_func_free(team);
	cancel_delayed_work_sync(&lb_priv->ex->stats.refresh_dw);
	free_percpu(lb_priv->pcpu_stats);
	kfree(lb_priv->ex);
}