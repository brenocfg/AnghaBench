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
struct m_property {int dummy; } ;
struct TYPE_2__ {scalar_t__ total_avsync_change; int /*<<< orphan*/  vo_chain; int /*<<< orphan*/  ao_chain; } ;
typedef  TYPE_1__ MPContext ;

/* Variables and functions */
 scalar_t__ MP_NOPTS_VALUE ; 
 int M_PROPERTY_UNAVAILABLE ; 
 int m_property_double_ro (int,void*,scalar_t__) ; 

__attribute__((used)) static int mp_property_total_avsync_change(void *ctx, struct m_property *prop,
                                           int action, void *arg)
{
    MPContext *mpctx = ctx;
    if (!mpctx->ao_chain || !mpctx->vo_chain)
        return M_PROPERTY_UNAVAILABLE;
    if (mpctx->total_avsync_change == MP_NOPTS_VALUE)
        return M_PROPERTY_UNAVAILABLE;
    return m_property_double_ro(action, arg, mpctx->total_avsync_change);
}