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
struct parport_uss720_private {int* reg; } ;
struct parport {struct parport_uss720_private* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ set_1284_register (struct parport*,int,unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void parport_uss720_data_forward (struct parport *pp)
{
	struct parport_uss720_private *priv = pp->private_data;	
	unsigned char d;

	d = priv->reg[1] & ~0x20;
	if (set_1284_register(pp, 2, d, GFP_KERNEL))
		return;
	priv->reg[1] = d;
}