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
struct TYPE_2__ {int active; int /*<<< orphan*/ * installfunc; int /*<<< orphan*/  (* changefunc ) (size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  add_dummy_choice () ; 
 int /*<<< orphan*/  change_openwith_choice (size_t) ; 
 size_t choice_count ; 
 TYPE_1__* choices ; 
 scalar_t__ has_gvim ; 
 int /*<<< orphan*/ * searchpath (char*) ; 

__attribute__((used)) static void
init_openwith_choice(void)
{
    if (has_gvim
#ifndef WIN3264
	    && searchpath("regedit.exe") != NULL
#endif
       )
    {
	choices[choice_count].changefunc = change_openwith_choice;
	choices[choice_count].installfunc = NULL;
	choices[choice_count].active = 1;
	change_openwith_choice(choice_count);  /* set the text */
	++choice_count;
    }
    else
	add_dummy_choice();
}