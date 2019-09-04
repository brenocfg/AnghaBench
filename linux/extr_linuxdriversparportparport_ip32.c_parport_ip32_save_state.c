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
struct TYPE_3__ {int /*<<< orphan*/  ecr; int /*<<< orphan*/  dcr; } ;
struct TYPE_4__ {TYPE_1__ ip32; } ;
struct parport_state {TYPE_2__ u; } ;
struct parport {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __parport_ip32_read_control (struct parport*) ; 
 int /*<<< orphan*/  parport_ip32_read_econtrol (struct parport*) ; 

__attribute__((used)) static void parport_ip32_save_state(struct parport *p,
				    struct parport_state *s)
{
	s->u.ip32.dcr = __parport_ip32_read_control(p);
	s->u.ip32.ecr = parport_ip32_read_econtrol(p);
}