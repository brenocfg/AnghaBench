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
 int __tsch (struct subchannel_id,struct irb*) ; 
 int /*<<< orphan*/  trace_s390_cio_tsch (struct subchannel_id,struct irb*,int) ; 

int tsch(struct subchannel_id schid, struct irb *addr)
{
	int ccode;

	ccode = __tsch(schid, addr);
	trace_s390_cio_tsch(schid, addr, ccode);

	return ccode;
}