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
struct comedi_subdevice {int dummy; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NI_M_CDIO_CMD_REG ; 
 int NI_M_CDO_CMD_DISARM ; 
 int NI_M_CDO_CMD_ERR_INT_ENA_CLR ; 
 int NI_M_CDO_CMD_F_E_INT_ENA_CLR ; 
 int NI_M_CDO_CMD_F_REQ_INT_ENA_CLR ; 
 int /*<<< orphan*/  NI_M_CDO_MASK_ENA_REG ; 
 int /*<<< orphan*/  ni_release_cdo_mite_channel (struct comedi_device*) ; 
 int /*<<< orphan*/  ni_writel (struct comedi_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ni_cdio_cancel(struct comedi_device *dev, struct comedi_subdevice *s)
{
	ni_writel(dev, NI_M_CDO_CMD_DISARM |
		       NI_M_CDO_CMD_ERR_INT_ENA_CLR |
		       NI_M_CDO_CMD_F_E_INT_ENA_CLR |
		       NI_M_CDO_CMD_F_REQ_INT_ENA_CLR,
		  NI_M_CDIO_CMD_REG);
	/*
	 * XXX not sure what interrupt C group does
	 * ni_writeb(dev, 0, NI_M_INTC_ENA_REG);
	 */
	ni_writel(dev, 0, NI_M_CDO_MASK_ENA_REG);
	ni_release_cdo_mite_channel(dev);
	return 0;
}