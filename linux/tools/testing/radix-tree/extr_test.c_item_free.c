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
struct item {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct item*) ; 
 int /*<<< orphan*/  item_sanity (struct item*,unsigned long) ; 

void item_free(struct item *item, unsigned long index)
{
	item_sanity(item, index);
	free(item);
}