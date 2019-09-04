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
struct mp_spherical_params {scalar_t__* ref_angles; scalar_t__ type; } ;

/* Variables and functions */

__attribute__((used)) static bool mp_spherical_equal(const struct mp_spherical_params *p1,
                               const struct mp_spherical_params *p2)
{
    for (int n = 0; n < 3; n++) {
        if (p1->ref_angles[n] != p2->ref_angles[n])
            return false;
    }
    return p1->type == p2->type;
}