#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ahd_softc {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
typedef  void* bus_size_t ;
typedef  TYPE_1__* bus_dma_tag_t ;
typedef  int /*<<< orphan*/  bus_dma_filter_t ;
struct TYPE_5__ {void* maxsize; void* boundary; void* alignment; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 TYPE_1__* kmalloc (int,int /*<<< orphan*/ ) ; 

int
ahd_dma_tag_create(struct ahd_softc *ahd, bus_dma_tag_t parent,
		   bus_size_t alignment, bus_size_t boundary,
		   dma_addr_t lowaddr, dma_addr_t highaddr,
		   bus_dma_filter_t *filter, void *filterarg,
		   bus_size_t maxsize, int nsegments,
		   bus_size_t maxsegsz, int flags, bus_dma_tag_t *ret_tag)
{
	bus_dma_tag_t dmat;

	dmat = kmalloc(sizeof(*dmat), GFP_ATOMIC);
	if (dmat == NULL)
		return (ENOMEM);

	/*
	 * Linux is very simplistic about DMA memory.  For now don't
	 * maintain all specification information.  Once Linux supplies
	 * better facilities for doing these operations, or the
	 * needs of this particular driver change, we might need to do
	 * more here.
	 */
	dmat->alignment = alignment;
	dmat->boundary = boundary;
	dmat->maxsize = maxsize;
	*ret_tag = dmat;
	return (0);
}