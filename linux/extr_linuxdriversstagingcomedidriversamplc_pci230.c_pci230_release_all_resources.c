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
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci230_release_shared (struct comedi_device*,unsigned char,unsigned int) ; 

__attribute__((used)) static void pci230_release_all_resources(struct comedi_device *dev,
					 unsigned int owner)
{
	pci230_release_shared(dev, (unsigned char)~0, owner);
}