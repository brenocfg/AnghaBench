#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut32 ;
struct TYPE_6__ {TYPE_1__* cfg; } ;
struct TYPE_5__ {int /*<<< orphan*/  end; int /*<<< orphan*/  g; } ;
typedef  TYPE_2__ EsilCfgGen ;

/* Variables and functions */
 int /*<<< orphan*/  _common_break_goto (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_graph_add_edge (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void _handle_break (EsilCfgGen *gen, ut32 id) {
	r_graph_add_edge (gen->cfg->g, _common_break_goto (gen, id), gen->cfg->end);
}