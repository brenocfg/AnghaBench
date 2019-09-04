#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct team_option_inst_info {unsigned char array_index; } ;
struct team {int dummy; } ;
struct lb_priv {TYPE_3__* ex; } ;
struct TYPE_5__ {TYPE_1__* info; } ;
struct TYPE_6__ {TYPE_2__ stats; } ;
struct TYPE_4__ {struct team_option_inst_info* opt_inst_info; } ;

/* Variables and functions */
 struct lb_priv* get_lb_priv (struct team*) ; 

__attribute__((used)) static int lb_hash_stats_init(struct team *team,
			      struct team_option_inst_info *info)
{
	struct lb_priv *lb_priv = get_lb_priv(team);
	unsigned char hash = info->array_index;

	lb_priv->ex->stats.info[hash].opt_inst_info = info;
	return 0;
}