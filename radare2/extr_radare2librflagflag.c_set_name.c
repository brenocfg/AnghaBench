#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* name; char* realname; } ;
typedef  TYPE_1__ RFlagItem ;

/* Variables and functions */
 int /*<<< orphan*/  free_item_name (TYPE_1__*) ; 
 int /*<<< orphan*/  free_item_realname (TYPE_1__*) ; 

__attribute__((used)) static void set_name(RFlagItem *item, char *name) {
	free_item_name (item);
	item->name = name;
	free_item_realname (item);
	item->realname = item->name;
}