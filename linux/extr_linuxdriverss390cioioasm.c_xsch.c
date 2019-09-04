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

/* Variables and functions */
 int __xsch (struct subchannel_id) ; 
 int /*<<< orphan*/  trace_s390_cio_xsch (struct subchannel_id,int) ; 

int xsch(struct subchannel_id schid)
{
	int ccode;

	ccode = __xsch(schid);
	trace_s390_cio_xsch(schid, ccode);

	return ccode;
}