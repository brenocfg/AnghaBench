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
struct wl_output {int dummy; } ;
struct vo_wayland_output {scalar_t__ scale; int /*<<< orphan*/  wl; } ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void output_handle_scale(void* data, struct wl_output *wl_output,
                                int32_t factor)
{
    struct vo_wayland_output *output = data;
    if (!factor) {
        MP_ERR(output->wl, "Invalid output scale given by the compositor!\n");
        return;
    }
    output->scale = factor;
}