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
struct wined3d_color_key {scalar_t__ color_space_low_value; scalar_t__ color_space_high_value; } ;
typedef  scalar_t__ DWORD ;
typedef  int BOOL ;

/* Variables and functions */

__attribute__((used)) static BOOL color_in_range(const struct wined3d_color_key *color_key, DWORD color)
{
    /* FIXME: Is this really how color keys are supposed to work? I think it
     * makes more sense to compare the individual channels. */
    return color >= color_key->color_space_low_value
            && color <= color_key->color_space_high_value;
}