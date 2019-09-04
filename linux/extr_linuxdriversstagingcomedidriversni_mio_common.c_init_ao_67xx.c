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
struct comedi_subdevice {int n_chan; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NI67XX_AO_CFG2_REG ; 
 int /*<<< orphan*/  NI67XX_AO_SP_UPDATES_REG ; 
 int NI_E_AO_DACSEL (int) ; 
 int /*<<< orphan*/  ni_ao_win_outw (struct comedi_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_ao_67xx(struct comedi_device *dev, struct comedi_subdevice *s)
{
	int i;

	for (i = 0; i < s->n_chan; i++) {
		ni_ao_win_outw(dev, NI_E_AO_DACSEL(i) | 0x0,
			       NI67XX_AO_CFG2_REG);
	}
	ni_ao_win_outw(dev, 0x0, NI67XX_AO_SP_UPDATES_REG);
}