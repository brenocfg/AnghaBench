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
struct color_fixup_desc {scalar_t__ w_sign_fixup; scalar_t__ z_sign_fixup; scalar_t__ y_sign_fixup; scalar_t__ x_sign_fixup; } ;
typedef  int BOOL ;

/* Variables and functions */

__attribute__((used)) static inline BOOL is_scaling_fixup(struct color_fixup_desc fixup)
{
    return fixup.x_sign_fixup || fixup.y_sign_fixup || fixup.z_sign_fixup || fixup.w_sign_fixup;
}