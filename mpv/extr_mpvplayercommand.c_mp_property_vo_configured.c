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
struct m_property {int dummy; } ;
struct TYPE_4__ {TYPE_1__* video_out; } ;
struct TYPE_3__ {scalar_t__ config_ok; } ;
typedef  TYPE_2__ MPContext ;

/* Variables and functions */
 int m_property_flag_ro (int,void*,int) ; 

__attribute__((used)) static int mp_property_vo_configured(void *ctx, struct m_property *prop,
                                     int action, void *arg)
{
    MPContext *mpctx = ctx;
    return m_property_flag_ro(action, arg,
                        mpctx->video_out && mpctx->video_out->config_ok);
}