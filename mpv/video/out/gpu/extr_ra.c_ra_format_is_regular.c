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
struct ra_format {int pixel_size; int num_components; scalar_t__* component_size; scalar_t__* component_depth; int /*<<< orphan*/  ordered; } ;

/* Variables and functions */

__attribute__((used)) static bool ra_format_is_regular(const struct ra_format *fmt)
{
    if (!fmt->pixel_size || !fmt->num_components || !fmt->ordered)
        return false;
    for (int n = 1; n < fmt->num_components; n++) {
        if (fmt->component_size[n] != fmt->component_size[0] ||
            fmt->component_depth[n] != fmt->component_depth[0])
            return false;
    }
    if (fmt->component_size[0] * fmt->num_components != fmt->pixel_size * 8)
        return false;
    return true;
}