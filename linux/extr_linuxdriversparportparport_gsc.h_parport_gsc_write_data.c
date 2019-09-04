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
struct parport {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA (struct parport*) ; 
 int /*<<< orphan*/  parport_writeb (unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void parport_gsc_write_data(struct parport *p, unsigned char d)
{
#ifdef DEBUG_PARPORT
	printk (KERN_DEBUG "parport_gsc_write_data(%p,0x%02x)\n", p, d);
#endif
	parport_writeb(d, DATA(p));
}