#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct parport_gsc_private {unsigned char ctr; unsigned char ctr_writable; } ;
struct parport {TYPE_1__* physport; } ;
struct TYPE_2__ {struct parport_gsc_private* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROL (struct parport*) ; 
 int /*<<< orphan*/  parport_writeb (unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned char __parport_gsc_frob_control(struct parport *p,
							unsigned char mask,
							unsigned char val)
{
	struct parport_gsc_private *priv = p->physport->private_data;
	unsigned char ctr = priv->ctr;
#ifdef DEBUG_PARPORT
	printk (KERN_DEBUG
		"__parport_gsc_frob_control(%02x,%02x): %02x -> %02x\n",
		mask, val, ctr, ((ctr & ~mask) ^ val) & priv->ctr_writable);
#endif
	ctr = (ctr & ~mask) ^ val;
	ctr &= priv->ctr_writable; /* only write writable bits. */
	parport_writeb (ctr, CONTROL (p));
	priv->ctr = ctr;	/* Update soft copy */
	return ctr;
}