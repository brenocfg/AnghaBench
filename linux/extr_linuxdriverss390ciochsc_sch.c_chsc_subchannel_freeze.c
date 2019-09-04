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
struct subchannel {int dummy; } ;

/* Variables and functions */
 int cio_disable_subchannel (struct subchannel*) ; 

__attribute__((used)) static int chsc_subchannel_freeze(struct subchannel *sch)
{
	return cio_disable_subchannel(sch);
}