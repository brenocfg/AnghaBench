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
struct wined3d_context {int lowest_disabled_stage; } ;
typedef  int BOOL ;

/* Variables and functions */

__attribute__((used)) static inline BOOL ffp_clip_emul(const struct wined3d_context *context)
{
    return context->lowest_disabled_stage < 7;
}