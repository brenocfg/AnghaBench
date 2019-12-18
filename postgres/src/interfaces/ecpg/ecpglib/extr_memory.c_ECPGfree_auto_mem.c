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
struct auto_mem {struct auto_mem* pointer; struct auto_mem* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  ecpg_free (struct auto_mem*) ; 
 struct auto_mem* get_auto_allocs () ; 
 int /*<<< orphan*/  set_auto_allocs (int /*<<< orphan*/ *) ; 

void
ECPGfree_auto_mem(void)
{
	struct auto_mem *am = get_auto_allocs();

	/* free all memory we have allocated for the user */
	if (am)
	{
		do
		{
			struct auto_mem *act = am;

			am = am->next;
			ecpg_free(act->pointer);
			ecpg_free(act);
		} while (am);
		set_auto_allocs(NULL);
	}
}