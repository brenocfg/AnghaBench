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
struct gs_init_data {int dummy; } ;
struct gs_swap_chain {int /*<<< orphan*/  wi; struct gs_init_data info; int /*<<< orphan*/ * device; } ;
typedef  struct gs_swap_chain gs_swapchain_t ;
typedef  int /*<<< orphan*/  gs_device_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 struct gs_swap_chain* bzalloc (int) ; 
 int /*<<< orphan*/  gl_platform_init_swapchain (struct gs_swap_chain*) ; 
 int /*<<< orphan*/  gl_windowinfo_create (struct gs_init_data const*) ; 
 int /*<<< orphan*/  gs_swapchain_destroy (struct gs_swap_chain*) ; 

gs_swapchain_t *device_swapchain_create(gs_device_t *device,
					const struct gs_init_data *info)
{
	struct gs_swap_chain *swap = bzalloc(sizeof(struct gs_swap_chain));

	swap->device = device;
	swap->info = *info;
	swap->wi = gl_windowinfo_create(info);
	if (!swap->wi) {
		blog(LOG_ERROR, "device_swapchain_create (GL) failed");
		gs_swapchain_destroy(swap);
		return NULL;
	}

	if (!gl_platform_init_swapchain(swap)) {
		blog(LOG_ERROR, "gl_platform_init_swapchain  failed");
		gs_swapchain_destroy(swap);
		return NULL;
	}

	return swap;
}