#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct m_property {int dummy; } ;
struct MPOpts {TYPE_1__* subs_rend; } ;
struct TYPE_5__ {struct MPOpts* opts; } ;
struct TYPE_4__ {int /*<<< orphan*/  sub_delay; } ;
typedef  TYPE_2__ MPContext ;

/* Variables and functions */
 int M_PROPERTY_OK ; 
#define  M_PROPERTY_PRINT 128 
 char* format_delay (int /*<<< orphan*/ ) ; 
 int mp_property_generic_option (TYPE_2__*,struct m_property*,int,void*) ; 

__attribute__((used)) static int mp_property_sub_delay(void *ctx, struct m_property *prop,
                                 int action, void *arg)
{
    MPContext *mpctx = ctx;
    struct MPOpts *opts = mpctx->opts;
    switch (action) {
    case M_PROPERTY_PRINT:
        *(char **)arg = format_delay(opts->subs_rend->sub_delay);
        return M_PROPERTY_OK;
    }
    return mp_property_generic_option(mpctx, prop, action, arg);
}