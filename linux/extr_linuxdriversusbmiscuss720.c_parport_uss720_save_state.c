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
struct parport_uss720_private {int /*<<< orphan*/ * reg; } ;
struct TYPE_3__ {int /*<<< orphan*/  ecr; int /*<<< orphan*/  ctr; } ;
struct TYPE_4__ {TYPE_1__ pc; } ;
struct parport_state {TYPE_2__ u; } ;
struct parport {struct parport_uss720_private* private_data; } ;

/* Variables and functions */

__attribute__((used)) static void parport_uss720_save_state(struct parport *pp, struct parport_state *s)
{
	struct parport_uss720_private *priv = pp->private_data;	

#if 0
	if (get_1284_register(pp, 2, NULL, GFP_ATOMIC))
		return;
#endif
	s->u.pc.ctr = priv->reg[1];
	s->u.pc.ecr = priv->reg[2];
}