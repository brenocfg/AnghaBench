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
struct mitem {void* usrptr; } ;
typedef  int /*<<< orphan*/  ITEM ;

/* Variables and functions */
 int /*<<< orphan*/ * current_item (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curses_menu ; 
 scalar_t__ item_userptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *item_data(void)
{
	ITEM *cur;
	struct mitem *mcur;

	cur = current_item(curses_menu);
	if (!cur)
		return NULL;
	mcur = (struct mitem *) item_userptr(cur);
	return mcur->usrptr;

}