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
struct spi_controller {int dummy; } ;
struct sg_table {int dummy; } ;
struct device {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static inline int spi_map_buf(struct spi_controller *ctlr, struct device *dev,
			      struct sg_table *sgt, void *buf, size_t len,
			      enum dma_data_direction dir)
{
	return -EINVAL;
}