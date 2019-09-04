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
struct crw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  trace_s390_cio_stcrw (struct crw*,int) ; 

int stcrw(struct crw *crw)
{
	int ccode;

	asm volatile(
		"	stcrw	0(%2)\n"
		"	ipm	%0\n"
		"	srl	%0,28\n"
		: "=d" (ccode), "=m" (*crw)
		: "a" (crw)
		: "cc");
	trace_s390_cio_stcrw(crw, ccode);

	return ccode;
}