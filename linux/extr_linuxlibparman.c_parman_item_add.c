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
struct parman_item {int dummy; } ;
struct parman {TYPE_1__* algo; } ;
struct TYPE_2__ {int (* item_add ) (struct parman*,struct parman_prio*,struct parman_item*) ;} ;

/* Variables and functions */
 int stub1 (struct parman*,struct parman_prio*,struct parman_item*) ; 

int parman_item_add(struct parman *parman, struct parman_prio *prio,
		    struct parman_item *item)
{
	return parman->algo->item_add(parman, prio, item);
}