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
struct cppi41_dma_controller {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cppi41_release_all_dma_chans (struct cppi41_dma_controller*) ; 

__attribute__((used)) static void cppi41_dma_controller_stop(struct cppi41_dma_controller *controller)
{
	cppi41_release_all_dma_chans(controller);
}