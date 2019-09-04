#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timespec64 {int dummy; } ;
struct pps_generator_pp {long port_write_time; TYPE_2__* pardev; } ;
struct parport {TYPE_1__* ops; } ;
struct TYPE_4__ {struct parport* port; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* write_control ) (struct parport*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NO_SIGNAL ; 
 int PORT_NTESTS_SHIFT ; 
 int /*<<< orphan*/  ktime_get_real_ts64 (struct timespec64*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  pr_info (char*,long) ; 
 int /*<<< orphan*/  stub1 (struct parport*,int /*<<< orphan*/ ) ; 
 struct timespec64 timespec64_sub (struct timespec64,struct timespec64) ; 
 scalar_t__ timespec64_to_ns (struct timespec64*) ; 

__attribute__((used)) static void calibrate_port(struct pps_generator_pp *dev)
{
	struct parport *port = dev->pardev->port;
	int i;
	long acc = 0;

	for (i = 0; i < (1 << PORT_NTESTS_SHIFT); i++) {
		struct timespec64 a, b;
		unsigned long irq_flags;

		local_irq_save(irq_flags);
		ktime_get_real_ts64(&a);
		port->ops->write_control(port, NO_SIGNAL);
		ktime_get_real_ts64(&b);
		local_irq_restore(irq_flags);

		b = timespec64_sub(b, a);
		acc += timespec64_to_ns(&b);
	}

	dev->port_write_time = acc >> PORT_NTESTS_SHIFT;
	pr_info("port write takes %ldns\n", dev->port_write_time);
}