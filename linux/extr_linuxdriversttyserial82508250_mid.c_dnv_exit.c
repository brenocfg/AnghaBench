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
struct mid8250 {int /*<<< orphan*/  dma_chip; int /*<<< orphan*/  dma_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  hsu_dma_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dnv_exit(struct mid8250 *mid)
{
	if (!mid->dma_dev)
		return;
	hsu_dma_remove(&mid->dma_chip);
}