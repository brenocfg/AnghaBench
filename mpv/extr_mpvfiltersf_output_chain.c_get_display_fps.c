#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mp_stream_info {struct chain* priv; } ;
struct chain {scalar_t__ vo; } ;

/* Variables and functions */
 int /*<<< orphan*/  VOCTRL_GET_DISPLAY_FPS ; 
 int /*<<< orphan*/  vo_control (scalar_t__,int /*<<< orphan*/ ,double*) ; 

__attribute__((used)) static double get_display_fps(struct mp_stream_info *i)
{
    struct chain *p = i->priv;
    double res = 0;
    if (p->vo)
        vo_control(p->vo, VOCTRL_GET_DISPLAY_FPS, &res);
    return res;
}