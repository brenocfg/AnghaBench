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
struct ni_gpct_device {int /*<<< orphan*/  variant; } ;
struct ni_gpct {unsigned int counter_index; struct ni_gpct_device* counter_dev; } ;

/* Variables and functions */
 unsigned int GI_PRESCALE_X2 (int /*<<< orphan*/ ) ; 
 unsigned int GI_PRESCALE_X8 (int /*<<< orphan*/ ) ; 
 int GI_SRC_POL_INVERT ; 
 int /*<<< orphan*/  NITIO_CNT_MODE_REG (unsigned int) ; 
 int /*<<< orphan*/  NITIO_INPUT_SEL_REG (unsigned int) ; 
 unsigned int NI_GPCT_INVERT_CLOCK_SRC_BIT ; 
 unsigned int NI_GPCT_PRESCALE_X2_CLOCK_SRC_BITS ; 
 unsigned int NI_GPCT_PRESCALE_X8_CLOCK_SRC_BITS ; 
 int ni_tio_get_soft_copy (struct ni_gpct const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int ni_tio_clock_src_modifiers(const struct ni_gpct *counter)
{
	struct ni_gpct_device *counter_dev = counter->counter_dev;
	unsigned int cidx = counter->counter_index;
	unsigned int counting_mode_bits =
		ni_tio_get_soft_copy(counter, NITIO_CNT_MODE_REG(cidx));
	unsigned int bits = 0;

	if (ni_tio_get_soft_copy(counter, NITIO_INPUT_SEL_REG(cidx)) &
	    GI_SRC_POL_INVERT)
		bits |= NI_GPCT_INVERT_CLOCK_SRC_BIT;
	if (counting_mode_bits & GI_PRESCALE_X2(counter_dev->variant))
		bits |= NI_GPCT_PRESCALE_X2_CLOCK_SRC_BITS;
	if (counting_mode_bits & GI_PRESCALE_X8(counter_dev->variant))
		bits |= NI_GPCT_PRESCALE_X8_CLOCK_SRC_BITS;
	return bits;
}