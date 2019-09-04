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
struct TYPE_3__ {int ecr; int /*<<< orphan*/  dcr; } ;
struct TYPE_4__ {TYPE_1__ ip32; } ;
struct parport_state {TYPE_2__ u; } ;
struct parport {int dummy; } ;

/* Variables and functions */
 int ECR_MODE_MASK ; 
 int /*<<< orphan*/  __parport_ip32_write_control (struct parport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parport_ip32_set_mode (struct parport*,int) ; 
 int /*<<< orphan*/  parport_ip32_write_econtrol (struct parport*,int) ; 

__attribute__((used)) static void parport_ip32_restore_state(struct parport *p,
				       struct parport_state *s)
{
	parport_ip32_set_mode(p, s->u.ip32.ecr & ECR_MODE_MASK);
	parport_ip32_write_econtrol(p, s->u.ip32.ecr);
	__parport_ip32_write_control(p, s->u.ip32.dcr);
}