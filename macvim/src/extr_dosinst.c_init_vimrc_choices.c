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
struct TYPE_2__ {int active; int /*<<< orphan*/ * installfunc; int /*<<< orphan*/  (* changefunc ) (size_t) ;int /*<<< orphan*/ * text; } ;

/* Variables and functions */
 scalar_t__ NUL ; 
 int /*<<< orphan*/  alloc_text (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  change_mouse_choice (size_t) ; 
 int /*<<< orphan*/  change_remap_choice (size_t) ; 
 int /*<<< orphan*/  change_run_choice (size_t) ; 
 int /*<<< orphan*/  change_vimrc_choice (size_t) ; 
 size_t choice_count ; 
 TYPE_1__* choices ; 
 size_t compat_choice ; 
 int /*<<< orphan*/ * compat_choices ; 
 int /*<<< orphan*/  compat_text ; 
 int /*<<< orphan*/ * install_vimrc ; 
 char* installdir ; 
 size_t mouse_choice ; 
 int /*<<< orphan*/ * mouse_choices ; 
 int /*<<< orphan*/  mouse_text ; 
 scalar_t__* oldvimrc ; 
 size_t remap_choice ; 
 int /*<<< orphan*/ * remap_choices ; 
 int /*<<< orphan*/  remap_text ; 
 scalar_t__ runtimeidx ; 
 int /*<<< orphan*/  strcpy (scalar_t__,char*) ; 
 scalar_t__ vimrc ; 

__attribute__((used)) static void
init_vimrc_choices(void)
{
    /* set path for a new _vimrc file (also when not used) */
    strcpy(vimrc, installdir);
    strcpy(vimrc + runtimeidx, "_vimrc");

    /* Set opposite value and then toggle it by calling change_vimrc_choice() */
    if (*oldvimrc == NUL)
	choices[choice_count].installfunc = NULL;
    else
	choices[choice_count].installfunc = install_vimrc;
    choices[choice_count].text = NULL;
    change_vimrc_choice(choice_count);
    choices[choice_count].changefunc = change_vimrc_choice;
    choices[choice_count].active = 1;
    ++choice_count;

    /* default way to run Vim */
    alloc_text(choice_count, compat_text, compat_choices[compat_choice]);
    choices[choice_count].changefunc = change_run_choice;
    choices[choice_count].installfunc = NULL;
    choices[choice_count].active = (*oldvimrc == NUL);
    ++choice_count;

    /* Whether to remap keys */
    alloc_text(choice_count, remap_text , remap_choices[remap_choice]);
    choices[choice_count].changefunc = change_remap_choice;
    choices[choice_count].installfunc = NULL;;
    choices[choice_count].active = (*oldvimrc == NUL);
    ++choice_count;

    /* default way to use the mouse */
    alloc_text(choice_count, mouse_text, mouse_choices[mouse_choice]);
    choices[choice_count].changefunc = change_mouse_choice;
    choices[choice_count].installfunc = NULL;;
    choices[choice_count].active = (*oldvimrc == NUL);
    ++choice_count;
}