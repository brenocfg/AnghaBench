#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct m_property {int dummy; } ;
struct TYPE_5__ {int play_dir; } ;
typedef  TYPE_1__ MPContext ;

/* Variables and functions */
 int /*<<< orphan*/  MPSEEK_ABSOLUTE ; 
 int /*<<< orphan*/  MPSEEK_EXACT ; 
 int M_PROPERTY_SET ; 
 int /*<<< orphan*/  get_current_time (TYPE_1__*) ; 
 int mp_property_generic_option (TYPE_1__*,struct m_property*,int,void*) ; 
 int /*<<< orphan*/  queue_seek (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mp_property_play_direction(void *ctx, struct m_property *prop,
                                      int action, void *arg)
{
    MPContext *mpctx = ctx;
    if (action == M_PROPERTY_SET) {
        if (mpctx->play_dir != *(int *)arg) {
            queue_seek(mpctx, MPSEEK_ABSOLUTE, get_current_time(mpctx),
                       MPSEEK_EXACT, 0);
        }
    }
    return mp_property_generic_option(mpctx, prop, action, arg);
}