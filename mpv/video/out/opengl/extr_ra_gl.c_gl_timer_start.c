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
struct ra_gl {int timer_active; TYPE_1__* gl; } ;
struct ra {struct ra_gl* priv; } ;
struct gl_timer {size_t idx; int active; int /*<<< orphan*/ * query; scalar_t__ result; } ;
typedef  struct gl_timer ra_timer ;
struct TYPE_2__ {int /*<<< orphan*/  (* BeginQuery ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* GetQueryObjectui64v ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ;scalar_t__ (* IsQuery ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ GL ;

/* Variables and functions */
 size_t GL_QUERY_OBJECT_NUM ; 
 int /*<<< orphan*/  GL_QUERY_RESULT ; 
 int /*<<< orphan*/  GL_TIME_ELAPSED ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gl_timer_start(struct ra *ra, ra_timer *ratimer)
{
    struct ra_gl *p = ra->priv;
    GL *gl = p->gl;
    struct gl_timer *timer = ratimer;

    // GL_TIME_ELAPSED queries are not re-entrant, so just do nothing instead
    // of crashing. Work-around for shitty GL limitations
    if (p->timer_active)
        return;

    // If this query object already contains a result, we need to retrieve it
    timer->result = 0;
    if (gl->IsQuery(timer->query[timer->idx])) {
        gl->GetQueryObjectui64v(timer->query[timer->idx], GL_QUERY_RESULT,
                                &timer->result);
    }

    gl->BeginQuery(GL_TIME_ELAPSED, timer->query[timer->idx++]);
    timer->idx %= GL_QUERY_OBJECT_NUM;

    p->timer_active = timer->active = true;
}