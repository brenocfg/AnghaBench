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
struct item {int index; } ;
struct idr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (struct item*) ; 
 struct item* idr_find (struct idr*,int) ; 
 int /*<<< orphan*/  idr_remove (struct idr*,int) ; 

void item_idr_remove(struct idr *idr, int id)
{
	struct item *item = idr_find(idr, id);
	assert(item->index == id);
	idr_remove(idr, id);
	free(item);
}