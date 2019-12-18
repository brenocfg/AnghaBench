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
struct mp_osd_res {int /*<<< orphan*/  w; } ;
struct m_property {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  osd; } ;
typedef  TYPE_1__ MPContext ;

/* Variables and functions */
 int m_property_int_ro (int,void*,int /*<<< orphan*/ ) ; 
 struct mp_osd_res osd_get_vo_res (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mp_property_osd_w(void *ctx, struct m_property *prop,
                             int action, void *arg)
{
    MPContext *mpctx = ctx;
    struct mp_osd_res vo_res = osd_get_vo_res(mpctx->osd);
    return m_property_int_ro(action, arg, vo_res.w);
}