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
struct pcs_device {unsigned int size; unsigned int bits_per_pin; unsigned int width; scalar_t__ bits_per_mux; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int BITS_PER_BYTE ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 

__attribute__((used)) static int pcs_get_pin_by_offset(struct pcs_device *pcs, unsigned offset)
{
	unsigned index;

	if (offset >= pcs->size) {
		dev_err(pcs->dev, "mux offset out of range: 0x%x (0x%x)\n",
			offset, pcs->size);
		return -EINVAL;
	}

	if (pcs->bits_per_mux)
		index = (offset * BITS_PER_BYTE) / pcs->bits_per_pin;
	else
		index = offset / (pcs->width / BITS_PER_BYTE);

	return index;
}