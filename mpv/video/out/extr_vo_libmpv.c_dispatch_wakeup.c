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
struct mpv_render_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  update (struct mpv_render_context*) ; 

__attribute__((used)) static void dispatch_wakeup(void *ptr)
{
    struct mpv_render_context *ctx = ptr;

    update(ctx);
}