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
struct parport {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIGB (struct parport*) ; 
 int /*<<< orphan*/  ECONTROL (struct parport*) ; 
 int /*<<< orphan*/  ECR_CNF ; 
 int /*<<< orphan*/  ECR_WRITE (struct parport*,unsigned char) ; 
 int PARPORT_DMA_NONE ; 
 int /*<<< orphan*/  frob_set_mode (struct parport*,int /*<<< orphan*/ ) ; 
 int inb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int programmable_dma_support(struct parport *p)
{
	unsigned char oecr = inb(ECONTROL(p));
	int dma;

	frob_set_mode(p, ECR_CNF);

	dma = inb(CONFIGB(p)) & 0x07;
	/* 000: Indicates jumpered 8-bit DMA if read-only.
	   100: Indicates jumpered 16-bit DMA if read-only. */
	if ((dma & 0x03) == 0)
		dma = PARPORT_DMA_NONE;

	ECR_WRITE(p, oecr);
	return dma;
}