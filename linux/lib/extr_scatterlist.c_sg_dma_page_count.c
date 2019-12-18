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
struct scatterlist {scalar_t__ offset; } ;

/* Variables and functions */
 int PAGE_ALIGN (scalar_t__) ; 
 int PAGE_SHIFT ; 
 scalar_t__ sg_dma_len (struct scatterlist*) ; 

__attribute__((used)) static int sg_dma_page_count(struct scatterlist *sg)
{
	return PAGE_ALIGN(sg->offset + sg_dma_len(sg)) >> PAGE_SHIFT;
}