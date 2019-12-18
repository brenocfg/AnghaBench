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

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 

void set_field(unsigned int *data, unsigned int field, unsigned int value)
{
	int i;

	if (WARN_ON(!field))
		return;
	/* @field should always be greater than 0 */
	for (i = 0; !(field & (1 << i)); )
		i++;

	*data = (*data & (~field)) | ((value << i) & field);
}