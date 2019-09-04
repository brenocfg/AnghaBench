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
struct priv {double pitch; scalar_t__ rubber; } ;

/* Variables and functions */
 int /*<<< orphan*/  rubberband_set_pitch_scale (scalar_t__,double) ; 

__attribute__((used)) static bool update_pitch(struct priv *p, double new_pitch)
{
    if (new_pitch < 0.01 || new_pitch > 100.0)
        return false;

    p->pitch = new_pitch;
    if (p->rubber)
        rubberband_set_pitch_scale(p->rubber, p->pitch);
    return true;
}