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
typedef  int u32 ;
struct iudma_ch {int n_bds_used; struct bcm_enet_desc* read_bd; struct bcm_enet_desc* bd_ring; struct bcm_enet_desc* end_bd; } ;
struct bcm_enet_desc {int len_stat; } ;
struct bcm63xx_udc {int dummy; } ;

/* Variables and functions */
 int DMADESC_LENGTH_MASK ; 
 int DMADESC_LENGTH_SHIFT ; 
 int DMADESC_OWNER_MASK ; 
 int EBUSY ; 
 int EINVAL ; 

__attribute__((used)) static int iudma_read(struct bcm63xx_udc *udc, struct iudma_ch *iudma)
{
	int i, actual_len = 0;
	struct bcm_enet_desc *d = iudma->read_bd;

	if (!iudma->n_bds_used)
		return -EINVAL;

	for (i = 0; i < iudma->n_bds_used; i++) {
		u32 dmaflags;

		dmaflags = d->len_stat;

		if (dmaflags & DMADESC_OWNER_MASK)
			return -EBUSY;

		actual_len += (dmaflags & DMADESC_LENGTH_MASK) >>
			      DMADESC_LENGTH_SHIFT;
		if (d == iudma->end_bd)
			d = iudma->bd_ring;
		else
			d++;
	}

	iudma->read_bd = d;
	iudma->n_bds_used = 0;
	return actual_len;
}