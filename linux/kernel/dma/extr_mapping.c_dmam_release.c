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
struct dma_devres {int /*<<< orphan*/  attrs; int /*<<< orphan*/  dma_handle; int /*<<< orphan*/  vaddr; int /*<<< orphan*/  size; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_attrs (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dmam_release(struct device *dev, void *res)
{
	struct dma_devres *this = res;

	dma_free_attrs(dev, this->size, this->vaddr, this->dma_handle,
			this->attrs);
}