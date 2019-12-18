#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vo_frame {int dummy; } ;
struct ra_swapchain {TYPE_1__* ctx; } ;
struct TYPE_2__ {int /*<<< orphan*/  ra; } ;

/* Variables and functions */
 int /*<<< orphan*/  ra_d3d11_flush (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool d3d11_submit_frame(struct ra_swapchain *sw,
                               const struct vo_frame *frame)
{
    ra_d3d11_flush(sw->ctx->ra);
    return true;
}