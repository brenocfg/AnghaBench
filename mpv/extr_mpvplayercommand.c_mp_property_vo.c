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
struct m_property {int dummy; } ;
struct TYPE_6__ {TYPE_2__* video_out; } ;
struct TYPE_5__ {TYPE_1__* driver; } ;
struct TYPE_4__ {int /*<<< orphan*/ * name; } ;
typedef  TYPE_3__ MPContext ;

/* Variables and functions */
 int m_property_strdup_ro (int,void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mp_property_vo(void *ctx, struct m_property *p, int action, void *arg)
{
    MPContext *mpctx = ctx;
    return m_property_strdup_ro(action, arg,
                    mpctx->video_out ? mpctx->video_out->driver->name : NULL);
}