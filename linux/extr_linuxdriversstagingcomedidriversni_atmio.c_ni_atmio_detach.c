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
struct pnp_dev {int dummy; } ;
struct comedi_device {scalar_t__ hw_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  comedi_legacy_detach (struct comedi_device*) ; 
 int /*<<< orphan*/  mio_common_detach (struct comedi_device*) ; 
 int /*<<< orphan*/  pnp_device_detach (struct pnp_dev*) ; 
 struct pnp_dev* to_pnp_dev (scalar_t__) ; 

__attribute__((used)) static void ni_atmio_detach(struct comedi_device *dev)
{
	struct pnp_dev *isapnp_dev;

	mio_common_detach(dev);
	comedi_legacy_detach(dev);

	isapnp_dev = dev->hw_dev ? to_pnp_dev(dev->hw_dev) : NULL;
	if (isapnp_dev)
		pnp_device_detach(isapnp_dev);
}