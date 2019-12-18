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
struct pci_device_id {int dummy; } ;
struct oxygen {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ get_xonar_cs43xx_model (struct oxygen*,struct pci_device_id const*) ; 
 scalar_t__ get_xonar_pcm179x_model (struct oxygen*,struct pci_device_id const*) ; 
 scalar_t__ get_xonar_wm87x6_model (struct oxygen*,struct pci_device_id const*) ; 

__attribute__((used)) static int get_xonar_model(struct oxygen *chip,
			   const struct pci_device_id *id)
{
	if (get_xonar_pcm179x_model(chip, id) >= 0)
		return 0;
	if (get_xonar_cs43xx_model(chip, id) >= 0)
		return 0;
	if (get_xonar_wm87x6_model(chip, id) >= 0)
		return 0;
	return -EINVAL;
}