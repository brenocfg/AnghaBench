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
struct dma_pool {struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_release (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dma_pool*) ; 
 int /*<<< orphan*/  dmam_pool_match ; 
 int /*<<< orphan*/  dmam_pool_release ; 

void dmam_pool_destroy(struct dma_pool *pool)
{
	struct device *dev = pool->dev;

	WARN_ON(devres_release(dev, dmam_pool_release, dmam_pool_match, pool));
}