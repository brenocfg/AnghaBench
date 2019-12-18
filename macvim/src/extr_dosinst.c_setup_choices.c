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
 int /*<<< orphan*/  init_bat_choices () ; 
 int /*<<< orphan*/  init_directories_choice () ; 
 int /*<<< orphan*/  init_openwith_choice () ; 
 int /*<<< orphan*/  init_popup_choice () ; 
 int /*<<< orphan*/  init_shortcut_choices () ; 
 int /*<<< orphan*/  init_startmenu_choice () ; 
 int /*<<< orphan*/  init_vimrc_choices () ; 

__attribute__((used)) static void
setup_choices(void)
{
    /* install the batch files */
    init_bat_choices();

    /* (over) write _vimrc file */
    init_vimrc_choices();

    /* Whether to add Vim to the popup menu */
    init_popup_choice();

    /* Whether to add Vim to the "Open With..." menu */
    init_openwith_choice();

    /* Whether to add Vim to the Start Menu. */
    init_startmenu_choice();

    /* Whether to add shortcuts to the Desktop. */
    init_shortcut_choices();

    /* Whether to create the runtime directories. */
    init_directories_choice();
}