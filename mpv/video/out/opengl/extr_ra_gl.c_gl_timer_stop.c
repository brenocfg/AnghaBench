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
typedef  int /*<<< orphan*/  uint64_t ;
struct ra_gl {int timer_active; TYPE_1__* gl; } ;
struct ra {struct ra_gl* priv; } ;
struct gl_timer {int active; int /*<<< orphan*/  result; } ;
typedef  struct gl_timer ra_timer ;
struct TYPE_2__ {int /*<<< orphan*/  (* EndQuery ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ GL ;

/* Variables and functions */
 int /*<<< orphan*/  GL_TIME_ELAPSED ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t gl_timer_stop(struct ra *ra, ra_timer *ratimer)
{
    struct ra_gl *p = ra->priv;
    GL *gl = p->gl;
    struct gl_timer *timer = ratimer;

    if (!timer->active)
        return 0;

    gl->EndQuery(GL_TIME_ELAPSED);
    p->timer_active = timer->active = false;

    return timer->result;
}