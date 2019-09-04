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
typedef  int uint32_t ;
typedef  int u_int ;
struct scb {int dummy; } ;
struct ahc_softc {int flags; int features; } ;
struct ahc_dma_seg {int /*<<< orphan*/  len; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int AHC_39BIT_ADDRESSING ; 
 int AHC_SG_LEN_MASK ; 
 int AHC_ULTRA2 ; 
 scalar_t__ DSCOMMAND1 ; 
 int HADDLDSEL0 ; 
 scalar_t__ HADDR ; 
 scalar_t__ HCNT ; 
 scalar_t__ SCB_RESIDUAL_DATACNT ; 
 scalar_t__ SCB_RESIDUAL_SGPTR ; 
 scalar_t__ SCB_TAG ; 
 int SG_HIGH_ADDR_BITS ; 
 int SG_PTR_MASK ; 
 scalar_t__ STCNT ; 
 int ahc_inb (struct ahc_softc*,scalar_t__) ; 
 int ahc_le32toh (int /*<<< orphan*/ ) ; 
 struct scb* ahc_lookup_scb (struct ahc_softc*,int) ; 
 int /*<<< orphan*/  ahc_outb (struct ahc_softc*,scalar_t__,int) ; 
 struct ahc_dma_seg* ahc_sg_bus_to_virt (struct scb*,int) ; 

__attribute__((used)) static void
ahc_reinitialize_dataptrs(struct ahc_softc *ahc)
{
	struct	 scb *scb;
	struct	 ahc_dma_seg *sg;
	u_int	 scb_index;
	uint32_t sgptr;
	uint32_t resid;
	uint32_t dataptr;

	scb_index = ahc_inb(ahc, SCB_TAG);
	scb = ahc_lookup_scb(ahc, scb_index);
	sgptr = (ahc_inb(ahc, SCB_RESIDUAL_SGPTR + 3) << 24)
	      | (ahc_inb(ahc, SCB_RESIDUAL_SGPTR + 2) << 16)
	      | (ahc_inb(ahc, SCB_RESIDUAL_SGPTR + 1) << 8)
	      |	ahc_inb(ahc, SCB_RESIDUAL_SGPTR);

	sgptr &= SG_PTR_MASK;
	sg = ahc_sg_bus_to_virt(scb, sgptr);

	/* The residual sg_ptr always points to the next sg */
	sg--;

	resid = (ahc_inb(ahc, SCB_RESIDUAL_DATACNT + 2) << 16)
	      | (ahc_inb(ahc, SCB_RESIDUAL_DATACNT + 1) << 8)
	      | ahc_inb(ahc, SCB_RESIDUAL_DATACNT);

	dataptr = ahc_le32toh(sg->addr)
		+ (ahc_le32toh(sg->len) & AHC_SG_LEN_MASK)
		- resid;
	if ((ahc->flags & AHC_39BIT_ADDRESSING) != 0) {
		u_int dscommand1;

		dscommand1 = ahc_inb(ahc, DSCOMMAND1);
		ahc_outb(ahc, DSCOMMAND1, dscommand1 | HADDLDSEL0);
		ahc_outb(ahc, HADDR,
			 (ahc_le32toh(sg->len) >> 24) & SG_HIGH_ADDR_BITS);
		ahc_outb(ahc, DSCOMMAND1, dscommand1);
	}
	ahc_outb(ahc, HADDR + 3, dataptr >> 24);
	ahc_outb(ahc, HADDR + 2, dataptr >> 16);
	ahc_outb(ahc, HADDR + 1, dataptr >> 8);
	ahc_outb(ahc, HADDR, dataptr);
	ahc_outb(ahc, HCNT + 2, resid >> 16);
	ahc_outb(ahc, HCNT + 1, resid >> 8);
	ahc_outb(ahc, HCNT, resid);
	if ((ahc->features & AHC_ULTRA2) == 0) {
		ahc_outb(ahc, STCNT + 2, resid >> 16);
		ahc_outb(ahc, STCNT + 1, resid >> 8);
		ahc_outb(ahc, STCNT, resid);
	}
}