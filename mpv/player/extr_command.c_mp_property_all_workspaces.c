#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct m_property {int dummy; } ;
struct TYPE_7__ {TYPE_2__* opts; } ;
struct TYPE_6__ {TYPE_1__* vo; } ;
struct TYPE_5__ {int /*<<< orphan*/  all_workspaces; } ;
typedef  TYPE_3__ MPContext ;

/* Variables and functions */
 int /*<<< orphan*/  VOCTRL_ALL_WORKSPACES ; 
 int mp_property_vo_flag (struct m_property*,int,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static int mp_property_all_workspaces(void *ctx, struct m_property *prop,
                                      int action, void *arg)
{
    MPContext *mpctx = ctx;
    return mp_property_vo_flag(prop, action, arg, VOCTRL_ALL_WORKSPACES,
                               &mpctx->opts->vo->all_workspaces, mpctx);
}