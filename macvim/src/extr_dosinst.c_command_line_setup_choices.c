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
struct TYPE_2__ {char* exenamearg; char* name; } ;

/* Variables and functions */
 int TARGET_COUNT ; 
 int /*<<< orphan*/ * getenv (char*) ; 
 scalar_t__ has_gvim ; 
 scalar_t__ has_vim ; 
 int /*<<< orphan*/  init_bat_choice (int) ; 
 int /*<<< orphan*/  init_directories_choice () ; 
 int /*<<< orphan*/  init_openwith_choice () ; 
 int /*<<< orphan*/  init_popup_choice () ; 
 int /*<<< orphan*/  init_shortcut_choices () ; 
 int /*<<< orphan*/  init_startmenu_choice () ; 
 int /*<<< orphan*/  init_vimrc_choices () ; 
 int /*<<< orphan*/  print_cmd_line_help () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 
 TYPE_1__* targets ; 
 int vimfiles_dir_choice ; 
 scalar_t__ vimfiles_dir_home ; 
 scalar_t__ vimfiles_dir_vim ; 

__attribute__((used)) static void
command_line_setup_choices(int argc, char **argv)
{
    int i, j;

    for (i = 1; i < argc; i++)
    {
	if (strcmp(argv[i], "-create-batfiles") == 0)
	{
	    if (i + 1 == argc)
		continue;
	    while (argv[i + 1][0] != '-' && i < argc)
	    {
		i++;
		for (j = 1; j < TARGET_COUNT; ++j)
		    if ((targets[j].exenamearg[0] == 'g' ? has_gvim : has_vim)
			    && strcmp(argv[i], targets[j].name) == 0)
		    {
			init_bat_choice(j);
			break;
		    }
		if (j == TARGET_COUNT)
		    printf("%s is not a valid choice for -create-batfiles\n",
								     argv[i]);

		if (i + 1 == argc)
		    break;
	    }
	}
	else if (strcmp(argv[i], "-create-vimrc") == 0)
	{
	    /* Setup default vimrc choices.  If there is already a _vimrc file,
	     * it will NOT be overwritten.
	     */
	    init_vimrc_choices();
	}
	else if (strcmp(argv[i], "-install-popup") == 0)
	{
	    init_popup_choice();
	}
	else if (strcmp(argv[i], "-install-openwith") == 0)
	{
	    init_openwith_choice();
	}
	else if (strcmp(argv[i], "-add-start-menu") == 0)
	{
	    init_startmenu_choice();
	}
	else if (strcmp(argv[i], "-install-icons") == 0)
	{
	    init_shortcut_choices();
	}
	else if (strcmp(argv[i], "-create-directories") == 0)
	{
	    init_directories_choice();
	    if (argv[i + 1][0] != '-')
	    {
		i++;
		if (strcmp(argv[i], "vim") == 0)
		    vimfiles_dir_choice = (int)vimfiles_dir_vim;
		else if (strcmp(argv[i], "home") == 0)
		{
		    if (getenv("HOME") == NULL) /* No $HOME in environment */
			vimfiles_dir_choice = (int)vimfiles_dir_vim;
		    else
			vimfiles_dir_choice = (int)vimfiles_dir_home;
		}
		else
		{
		    printf("Unknown argument for -create-directories: %s\n",
								     argv[i]);
		    print_cmd_line_help();
		}
	    }
	    else /* No choice specified, default to vim directory */
		vimfiles_dir_choice = (int)vimfiles_dir_vim;
	}
#ifdef WIN3264
	else if (strcmp(argv[i], "-register-OLE") == 0)
	{
	    /* This is always done when gvim is found */
	}
#endif
	else /* Unknown switch */
	{
	    printf("Got unknown argument argv[%d] = %s\n", i, argv[i]);
	    print_cmd_line_help();
	}
    }
}