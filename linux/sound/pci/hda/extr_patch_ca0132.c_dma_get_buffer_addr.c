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
struct dma_engine {TYPE_1__* dmab; } ;
struct TYPE_2__ {unsigned char* area; } ;

/* Variables and functions */

__attribute__((used)) static unsigned char *dma_get_buffer_addr(struct dma_engine *dma)
{
	return dma->dmab->area;
}