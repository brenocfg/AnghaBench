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
struct TYPE_2__ {scalar_t__ ao; } ;
typedef  TYPE_1__ MPContext ;

/* Variables and functions */
 int /*<<< orphan*/ * ao_get_name (scalar_t__) ; 
 int m_property_strdup_ro (int,void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mp_property_ao(void *ctx, struct m_property *p, int action, void *arg)
{
    MPContext *mpctx = ctx;
    return m_property_strdup_ro(action, arg,
                                    mpctx->ao ? ao_get_name(mpctx->ao) : NULL);
}