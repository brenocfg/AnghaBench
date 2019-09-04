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
struct parman_prio {int dummy; } ;
struct TYPE_2__ {unsigned long index; } ;

/* Variables and functions */
 TYPE_1__* parman_prio_last_item (struct parman_prio*) ; 

__attribute__((used)) static unsigned long parman_prio_last_index(struct parman_prio *prio)
{
	return parman_prio_last_item(prio)->index;
}