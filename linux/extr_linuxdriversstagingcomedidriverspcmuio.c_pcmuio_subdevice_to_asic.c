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
struct comedi_subdevice {int index; } ;

/* Variables and functions */

__attribute__((used)) static inline int pcmuio_subdevice_to_asic(struct comedi_subdevice *s)
{
	/*
	 * subdevice 0 and 1 are handled by the first asic
	 * subdevice 2 and 3 are handled by the second asic
	 */
	return s->index / 2;
}