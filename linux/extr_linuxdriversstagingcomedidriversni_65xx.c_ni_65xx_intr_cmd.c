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
struct comedi_device {scalar_t__ mmio; } ;

/* Variables and functions */
 int NI_65XX_CLR_EDGE_INT ; 
 int NI_65XX_CLR_OVERFLOW_INT ; 
 scalar_t__ NI_65XX_CLR_REG ; 
 int NI_65XX_CTRL_EDGE_ENA ; 
 int NI_65XX_CTRL_FALL_EDGE_ENA ; 
 int NI_65XX_CTRL_INT_ENA ; 
 scalar_t__ NI_65XX_CTRL_REG ; 
 int NI_65XX_CTRL_RISE_EDGE_ENA ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static int ni_65xx_intr_cmd(struct comedi_device *dev,
			    struct comedi_subdevice *s)
{
	writeb(NI_65XX_CLR_EDGE_INT | NI_65XX_CLR_OVERFLOW_INT,
	       dev->mmio + NI_65XX_CLR_REG);
	writeb(NI_65XX_CTRL_FALL_EDGE_ENA | NI_65XX_CTRL_RISE_EDGE_ENA |
	       NI_65XX_CTRL_INT_ENA | NI_65XX_CTRL_EDGE_ENA,
	       dev->mmio + NI_65XX_CTRL_REG);

	return 0;
}