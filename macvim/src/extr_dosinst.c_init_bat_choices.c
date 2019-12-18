#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int active; scalar_t__ arg; int /*<<< orphan*/ * installfunc; int /*<<< orphan*/  changefunc; int /*<<< orphan*/  text; } ;
struct TYPE_3__ {char* exenamearg; int /*<<< orphan*/ * oldexe; } ;

/* Variables and functions */
 int TARGET_COUNT ; 
 int /*<<< orphan*/  add_dummy_choice () ; 
 int /*<<< orphan*/  bat_text_yes ; 
 int /*<<< orphan*/  change_main_bat_choice ; 
 size_t choice_count ; 
 TYPE_2__* choices ; 
 scalar_t__ has_gvim ; 
 scalar_t__ has_vim ; 
 int /*<<< orphan*/  init_bat_choice (int) ; 
 TYPE_1__* targets ; 

__attribute__((used)) static void
init_bat_choices(void)
{
    int		i;

    /* The first item is used to switch installing batch files on/off and
     * setting the default path. */
    choices[choice_count].text = bat_text_yes;
    choices[choice_count].changefunc = change_main_bat_choice;
    choices[choice_count].installfunc = NULL;
    choices[choice_count].active = 1;
    choices[choice_count].arg = 0;
    ++choice_count;

    /* Add items for each batch file target.  Only used when not disabled by
     * the first item.  When a .exe exists, don't offer to create a .bat. */
    for (i = 1; i < TARGET_COUNT; ++i)
	if (targets[i].oldexe == NULL
		&& (targets[i].exenamearg[0] == 'g' ? has_gvim : has_vim))
	    init_bat_choice(i);
	else
	    add_dummy_choice();
}