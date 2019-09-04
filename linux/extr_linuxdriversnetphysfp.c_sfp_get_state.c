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
struct sfp {unsigned int (* get_state ) (struct sfp*) ;} ;

/* Variables and functions */
 unsigned int stub1 (struct sfp*) ; 

__attribute__((used)) static unsigned int sfp_get_state(struct sfp *sfp)
{
	return sfp->get_state(sfp);
}