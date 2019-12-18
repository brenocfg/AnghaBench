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
struct TYPE_2__ {int /*<<< orphan*/  installfunc; int /*<<< orphan*/  (* changefunc ) (size_t) ;void* active; scalar_t__ arg; int /*<<< orphan*/ * text; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_dummy_choice () ; 
 size_t choice_count ; 
 TYPE_1__* choices ; 
 void* has_gvim ; 
 int /*<<< orphan*/  install_shortcut_evim ; 
 int /*<<< orphan*/  install_shortcut_gview ; 
 int /*<<< orphan*/  install_shortcut_gvim ; 
 int /*<<< orphan*/  toggle_shortcut_choice (size_t) ; 

__attribute__((used)) static void
init_shortcut_choices(void)
{
#ifdef WIN3264
    /* Shortcut to gvim */
    choices[choice_count].text = NULL;
    choices[choice_count].arg = 0;
    choices[choice_count].active = has_gvim;
    choices[choice_count].changefunc = toggle_shortcut_choice;
    choices[choice_count].installfunc = install_shortcut_gvim;
    toggle_shortcut_choice(choice_count);
    ++choice_count;

    /* Shortcut to evim */
    choices[choice_count].text = NULL;
    choices[choice_count].arg = 0;
    choices[choice_count].active = has_gvim;
    choices[choice_count].changefunc = toggle_shortcut_choice;
    choices[choice_count].installfunc = install_shortcut_evim;
    toggle_shortcut_choice(choice_count);
    ++choice_count;

    /* Shortcut to gview */
    choices[choice_count].text = NULL;
    choices[choice_count].arg = 0;
    choices[choice_count].active = has_gvim;
    choices[choice_count].changefunc = toggle_shortcut_choice;
    choices[choice_count].installfunc = install_shortcut_gview;
    toggle_shortcut_choice(choice_count);
    ++choice_count;
#else
    add_dummy_choice();
    add_dummy_choice();
    add_dummy_choice();
#endif
}