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
struct ax_drvdata {int /*<<< orphan*/  spp_spr; } ;

/* Variables and functions */
 unsigned int AX_SPR_ACK ; 
 unsigned int AX_SPR_BUSY ; 
 unsigned int AX_SPR_ERR ; 
 unsigned int AX_SPR_PE ; 
 unsigned int AX_SPR_SLCT ; 
 unsigned int PARPORT_STATUS_ACK ; 
 unsigned int PARPORT_STATUS_BUSY ; 
 unsigned int PARPORT_STATUS_ERROR ; 
 unsigned int PARPORT_STATUS_PAPEROUT ; 
 unsigned int PARPORT_STATUS_SELECT ; 
 struct ax_drvdata* pp_to_drv (struct parport*) ; 
 unsigned int readb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned char
parport_ax88796_read_status(struct parport *p)
{
	struct ax_drvdata *dd = pp_to_drv(p);
	unsigned int status = readb(dd->spp_spr);
	unsigned int ret = 0;

	if (status & AX_SPR_BUSY)
		ret |= PARPORT_STATUS_BUSY;

	if (status & AX_SPR_ACK)
		ret |= PARPORT_STATUS_ACK;

	if (status & AX_SPR_ERR)
		ret |= PARPORT_STATUS_ERROR;

	if (status & AX_SPR_SLCT)
		ret |= PARPORT_STATUS_SELECT;

	if (status & AX_SPR_PE)
		ret |= PARPORT_STATUS_PAPEROUT;

	return ret;
}