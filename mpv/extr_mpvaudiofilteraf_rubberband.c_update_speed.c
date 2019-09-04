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
struct priv {double speed; scalar_t__ rubber; } ;

/* Variables and functions */
 int /*<<< orphan*/  rubberband_set_time_ratio (scalar_t__,double) ; 

__attribute__((used)) static void update_speed(struct priv *p, double new_speed)
{
    p->speed = new_speed;
    if (p->rubber)
        rubberband_set_time_ratio(p->rubber, 1.0 / p->speed);
}