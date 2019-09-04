#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ecr; int /*<<< orphan*/  ctr; } ;
struct TYPE_6__ {TYPE_2__ pc; } ;
struct parport_state {TYPE_3__ u; } ;
struct parport_pc_private {scalar_t__ ecr; int /*<<< orphan*/  ctr; } ;
struct parport {TYPE_1__* physport; } ;
struct TYPE_4__ {struct parport_pc_private* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECONTROL (struct parport*) ; 
 int /*<<< orphan*/  inb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void parport_pc_save_state(struct parport *p, struct parport_state *s)
{
	const struct parport_pc_private *priv = p->physport->private_data;
	s->u.pc.ctr = priv->ctr;
	if (priv->ecr)
		s->u.pc.ecr = inb(ECONTROL(p));
}