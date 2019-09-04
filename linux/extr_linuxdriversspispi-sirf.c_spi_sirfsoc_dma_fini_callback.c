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
struct completion {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (struct completion*) ; 

__attribute__((used)) static void spi_sirfsoc_dma_fini_callback(void *data)
{
	struct completion *dma_complete = data;

	complete(dma_complete);
}