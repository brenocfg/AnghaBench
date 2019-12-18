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
 int TABLE_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_choice (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * getenv (char*) ; 
 int /*<<< orphan*/  set_directories_text (int) ; 
 int /*<<< orphan*/  vimfiles_dir_choice ; 
 int /*<<< orphan*/  vimfiles_dir_choices ; 

__attribute__((used)) static void
change_directories_choice(int idx)
{
    int	    choice_count = TABLE_SIZE(vimfiles_dir_choices);

    /* Don't offer the $HOME choice if $HOME isn't set. */
    if (getenv("HOME") == NULL)
	--choice_count;
    vimfiles_dir_choice = get_choice(vimfiles_dir_choices, choice_count);
    set_directories_text(idx);
}