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
 int /*<<< orphan*/  AB8500_AUDIO ; 
 int abx500_set_register_interruptible (struct device*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static int ab8500_codec_write_reg(void *context, unsigned int reg,
				  unsigned int value)
{
	struct device *dev = context;

	return abx500_set_register_interruptible(dev, AB8500_AUDIO,
						 reg, value);
}