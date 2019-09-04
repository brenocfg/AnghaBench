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
typedef  size_t u8 ;
struct skl_module_res {scalar_t__ cps; } ;
struct skl_module_cfg {size_t res_idx; TYPE_1__* module; } ;
struct TYPE_4__ {int /*<<< orphan*/  mcps; } ;
struct skl {TYPE_2__ resource; } ;
struct TYPE_3__ {struct skl_module_res* resources; } ;

/* Variables and functions */

__attribute__((used)) static void
skl_tplg_free_pipe_mcps(struct skl *skl, struct skl_module_cfg *mconfig)
{
	u8 res_idx = mconfig->res_idx;
	struct skl_module_res *res = &mconfig->module->resources[res_idx];

	skl->resource.mcps -= res->cps;
}