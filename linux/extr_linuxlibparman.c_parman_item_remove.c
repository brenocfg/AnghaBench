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
struct TYPE_2__ {int /*<<< orphan*/  (* item_remove ) (struct parman*,struct parman_prio*,struct parman_item*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct parman*,struct parman_prio*,struct parman_item*) ; 

void parman_item_remove(struct parman *parman, struct parman_prio *prio,
			struct parman_item *item)
{
	parman->algo->item_remove(parman, prio, item);
}