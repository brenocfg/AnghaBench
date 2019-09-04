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
struct scb {scalar_t__ sg_count; TYPE_1__* platform_data; } ;
struct ahc_softc {int flags; } ;
struct ahc_dma_seg {void* len; void* addr; } ;
typedef  int dma_addr_t ;
typedef  int bus_size_t ;
struct TYPE_2__ {int xfer_len; } ;

/* Variables and functions */
 int AHC_39BIT_ADDRESSING ; 
 scalar_t__ AHC_NSEG ; 
 int AHC_SG_HIGH_ADDR_MASK ; 
 void* ahc_htole32 (int) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static int
ahc_linux_map_seg(struct ahc_softc *ahc, struct scb *scb,
		  struct ahc_dma_seg *sg, dma_addr_t addr, bus_size_t len)
{
	int	 consumed;

	if ((scb->sg_count + 1) > AHC_NSEG)
		panic("Too few segs for dma mapping.  "
		      "Increase AHC_NSEG\n");

	consumed = 1;
	sg->addr = ahc_htole32(addr & 0xFFFFFFFF);
	scb->platform_data->xfer_len += len;

	if (sizeof(dma_addr_t) > 4
	 && (ahc->flags & AHC_39BIT_ADDRESSING) != 0)
		len |= (addr >> 8) & AHC_SG_HIGH_ADDR_MASK;

	sg->len = ahc_htole32(len);
	return (consumed);
}