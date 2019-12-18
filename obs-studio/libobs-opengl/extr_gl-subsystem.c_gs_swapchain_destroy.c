#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  wi; TYPE_4__* device; } ;
typedef  TYPE_1__ gs_swapchain_t ;
struct TYPE_7__ {TYPE_1__* cur_swap; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (TYPE_1__*) ; 
 int /*<<< orphan*/  device_load_swapchain (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gl_platform_cleanup_swapchain (TYPE_1__*) ; 
 int /*<<< orphan*/  gl_windowinfo_destroy (int /*<<< orphan*/ ) ; 

void gs_swapchain_destroy(gs_swapchain_t *swapchain)
{
	if (!swapchain)
		return;

	if (swapchain->device->cur_swap == swapchain)
		device_load_swapchain(swapchain->device, NULL);

	gl_platform_cleanup_swapchain(swapchain);

	gl_windowinfo_destroy(swapchain->wi);
	bfree(swapchain);
}