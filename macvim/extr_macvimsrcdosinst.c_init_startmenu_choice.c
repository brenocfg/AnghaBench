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

/* Variables and functions */
 int /*<<< orphan*/  add_dummy_choice () ; 

__attribute__((used)) static void
init_startmenu_choice(void)
{
#ifdef WIN3264
    /* Start menu */
    choices[choice_count].changefunc = toggle_startmenu_choice;
    choices[choice_count].installfunc = NULL;
    choices[choice_count].active = 1;
    toggle_startmenu_choice(choice_count);	/* set the text */
    ++choice_count;
#else
    add_dummy_choice();
#endif
}