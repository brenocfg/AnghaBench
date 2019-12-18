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
struct priv {float speed; double scale; int frames_stride_scaled; int frames_stride; int /*<<< orphan*/  frames_stride_error; TYPE_1__* opts; } ;
struct TYPE_2__ {int speed_opt; double scale_nominal; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPMIN (int /*<<< orphan*/ ,int) ; 
 int SCALE_PITCH ; 

__attribute__((used)) static void update_speed(struct priv *s, float speed)
{
    s->speed = speed;

    double factor = (s->opts->speed_opt & SCALE_PITCH) ? 1.0 / s->speed : s->speed;
    s->scale = factor * s->opts->scale_nominal;

    s->frames_stride_scaled = s->scale * s->frames_stride;
    s->frames_stride_error = MPMIN(s->frames_stride_error, s->frames_stride_scaled);
}