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
struct device {int dummy; } ;

/* Variables and functions */
 int pcm179x_accessible_reg (struct device*,unsigned int) ; 

__attribute__((used)) static bool pcm179x_writeable_reg(struct device *dev, unsigned int reg)
{
	bool accessible;

	accessible = pcm179x_accessible_reg(dev, reg);

	return accessible && reg != 0x16 && reg != 0x17;
}