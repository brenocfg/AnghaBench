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
struct comedi_device {int /*<<< orphan*/  pacer; } ;

/* Variables and functions */
 int /*<<< orphan*/  comedi_8254_cascade_ns_to_timer (int /*<<< orphan*/ ,unsigned int*,unsigned int) ; 
 int /*<<< orphan*/  comedi_8254_pacer_enable (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  comedi_8254_update_divisors (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int das16_set_pacer(struct comedi_device *dev, unsigned int ns,
				    unsigned int flags)
{
	comedi_8254_cascade_ns_to_timer(dev->pacer, &ns, flags);
	comedi_8254_update_divisors(dev->pacer);
	comedi_8254_pacer_enable(dev->pacer, 1, 2, true);

	return ns;
}