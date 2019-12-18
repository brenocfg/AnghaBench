#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * local; int /*<<< orphan*/ * name; } ;
struct TYPE_5__ {int nItems; int itemFlags; TYPE_3__* items; } ;
typedef  int /*<<< orphan*/  IndexSubItem ;
typedef  TYPE_1__ IndexItem ;

/* Variables and functions */
 TYPE_3__* heap_realloc (TYPE_3__*,int) ; 

__attribute__((used)) static void item_realloc(IndexItem *item, int num_items)
{
    item->nItems = num_items;
    item->items = heap_realloc(item->items, sizeof(IndexSubItem)*item->nItems);
    item->items[item->nItems-1].name = NULL;
    item->items[item->nItems-1].local = NULL;
    item->itemFlags = 0x00;
}