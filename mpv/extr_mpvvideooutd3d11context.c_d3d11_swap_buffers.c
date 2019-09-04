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
struct ra_swapchain {struct priv* priv; } ;
struct priv {TYPE_1__* opts; int /*<<< orphan*/  swapchain; } ;
struct TYPE_2__ {int /*<<< orphan*/  sync_interval; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDXGISwapChain_Present (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void d3d11_swap_buffers(struct ra_swapchain *sw)
{
    struct priv *p = sw->priv;
    IDXGISwapChain_Present(p->swapchain, p->opts->sync_interval, 0);
}