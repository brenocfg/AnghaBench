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
struct stat {int dummy; } ;
struct TYPE_2__ {int active; int /*<<< orphan*/  installfunc; int /*<<< orphan*/  changefunc; int /*<<< orphan*/  text; } ;

/* Variables and functions */
 int BUFSIZE ; 
 int /*<<< orphan*/  alloc (int) ; 
 int /*<<< orphan*/  change_directories_choice ; 
 size_t choice_count ; 
 TYPE_1__* choices ; 
 int /*<<< orphan*/  dir_remove_last (int /*<<< orphan*/ ,char*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  install_vimfilesdir ; 
 int /*<<< orphan*/  installdir ; 
 int /*<<< orphan*/  set_directories_text (size_t) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int vimfiles_dir_choice ; 
 scalar_t__ vimfiles_dir_home ; 
 scalar_t__ vimfiles_dir_none ; 
 scalar_t__ vimfiles_dir_vim ; 

__attribute__((used)) static void
init_directories_choice(void)
{
    struct stat	st;
    char	tmp_dirname[BUFSIZE];
    char	*p;

    choices[choice_count].text = alloc(150);
    choices[choice_count].changefunc = change_directories_choice;
    choices[choice_count].installfunc = install_vimfilesdir;
    choices[choice_count].active = 1;

    /* Check if the "compiler" directory already exists.  That's a good
     * indication that the plugin directories were already created. */
    if (getenv("HOME") != NULL)
    {
	vimfiles_dir_choice = (int)vimfiles_dir_home;
	sprintf(tmp_dirname, "%s\\vimfiles\\compiler", getenv("HOME"));
	if (stat(tmp_dirname, &st) == 0)
	    vimfiles_dir_choice = (int)vimfiles_dir_none;
    }
    else
    {
	vimfiles_dir_choice = (int)vimfiles_dir_vim;
	p = getenv("VIM");
	if (p == NULL) /* No $VIM in path, use the install dir */
	    dir_remove_last(installdir, tmp_dirname);
	else
	    strcpy(tmp_dirname, p);
	strcat(tmp_dirname, "\\vimfiles\\compiler");
	if (stat(tmp_dirname, &st) == 0)
	    vimfiles_dir_choice = (int)vimfiles_dir_none;
    }

    set_directories_text(choice_count);
    ++choice_count;
}