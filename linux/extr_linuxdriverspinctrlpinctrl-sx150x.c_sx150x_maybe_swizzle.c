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
struct sx150x_pinctrl {struct sx150x_device_data* data; } ;
struct sx150x_device_data {unsigned int reg_sense; int ngpios; scalar_t__ model; } ;

/* Variables and functions */
 scalar_t__ SX150X_123 ; 
 scalar_t__ SX150X_456 ; 

__attribute__((used)) static unsigned int sx150x_maybe_swizzle(struct sx150x_pinctrl *pctl,
					 unsigned int reg, unsigned int val)
{
	unsigned int a, b;
	const struct sx150x_device_data *data = pctl->data;

	/*
	 * Whereas SX1509 presents RegSense in a simple layout as such:
	 *	reg     [ f f e e d d c c ]
	 *	reg + 1 [ b b a a 9 9 8 8 ]
	 *	reg + 2 [ 7 7 6 6 5 5 4 4 ]
	 *	reg + 3 [ 3 3 2 2 1 1 0 0 ]
	 *
	 * SX1503 and SX1506 deviate from that data layout, instead storing
	 * their contents as follows:
	 *
	 *	reg     [ f f e e d d c c ]
	 *	reg + 1 [ 7 7 6 6 5 5 4 4 ]
	 *	reg + 2 [ b b a a 9 9 8 8 ]
	 *	reg + 3 [ 3 3 2 2 1 1 0 0 ]
	 *
	 * so, taking that into account, we swap two
	 * inner bytes of a 4-byte result
	 */

	if (reg == data->reg_sense &&
	    data->ngpios == 16 &&
	    (data->model == SX150X_123 ||
	     data->model == SX150X_456)) {
		a = val & 0x00ff0000;
		b = val & 0x0000ff00;

		val &= 0xff0000ff;
		val |= b << 8;
		val |= a >> 8;
	}

	return val;
}