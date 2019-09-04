#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pnp_dev {TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ check_name (int /*<<< orphan*/ ) ; 
 scalar_t__ check_resources (struct pnp_dev*) ; 
 int /*<<< orphan*/  pnp_dev_name (struct pnp_dev*) ; 

__attribute__((used)) static int serial_pnp_guess_board(struct pnp_dev *dev)
{
	if (!(check_name(pnp_dev_name(dev)) ||
	    (dev->card && check_name(dev->card->name))))
		return -ENODEV;

	if (check_resources(dev))
		return 0;

	return -ENODEV;
}