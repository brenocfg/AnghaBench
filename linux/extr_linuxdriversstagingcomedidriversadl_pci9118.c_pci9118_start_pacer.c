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
struct comedi_device {int /*<<< orphan*/  pacer; } ;

/* Variables and functions */
 int /*<<< orphan*/  comedi_8254_pacer_enable (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void pci9118_start_pacer(struct comedi_device *dev, int mode)
{
	if (mode == 1 || mode == 2 || mode == 4)
		comedi_8254_pacer_enable(dev->pacer, 1, 2, true);
}