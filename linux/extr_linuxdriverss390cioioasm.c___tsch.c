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
struct subchannel_id {int dummy; } ;
struct irb {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int __tsch(struct subchannel_id schid, struct irb *addr)
{
	register struct subchannel_id reg1 asm ("1") = schid;
	int ccode;

	asm volatile(
		"	tsch	0(%3)\n"
		"	ipm	%0\n"
		"	srl	%0,28"
		: "=d" (ccode), "=m" (*addr)
		: "d" (reg1), "a" (addr)
		: "cc");
	return ccode;
}