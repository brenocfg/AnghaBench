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
struct wined3d_matrix {float member_0; float member_1; float member_2; float member_3; float member_4; float member_5; float member_6; float member_7; float member_8; float member_9; float member_10; float member_11; float member_12; float member_13; float member_14; float member_15; } ;

/* Variables and functions */

void get_identity_matrix(struct wined3d_matrix *mat)
{
    static const struct wined3d_matrix identity =
    {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
    };

    *mat = identity;
}