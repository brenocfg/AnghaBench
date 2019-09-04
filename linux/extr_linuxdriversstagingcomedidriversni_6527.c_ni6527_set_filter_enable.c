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
struct comedi_device {scalar_t__ mmio; } ;

/* Variables and functions */
 scalar_t__ NI6527_FILT_ENA_REG (int) ; 
 int /*<<< orphan*/  writeb (unsigned int,scalar_t__) ; 

__attribute__((used)) static void ni6527_set_filter_enable(struct comedi_device *dev,
				     unsigned int val)
{
	writeb(val & 0xff, dev->mmio + NI6527_FILT_ENA_REG(0));
	writeb((val >> 8) & 0xff, dev->mmio + NI6527_FILT_ENA_REG(1));
	writeb((val >> 16) & 0xff, dev->mmio + NI6527_FILT_ENA_REG(2));
}