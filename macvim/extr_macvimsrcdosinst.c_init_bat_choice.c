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
struct TYPE_4__ {int arg; int active; int /*<<< orphan*/  (* changefunc ) (size_t) ;int /*<<< orphan*/ * text; int /*<<< orphan*/  installfunc; } ;
struct TYPE_3__ {char* batpath; char* oldbat; int /*<<< orphan*/  batname; } ;

/* Variables and functions */
 char NUL ; 
 int /*<<< orphan*/  add_pathsep (char*) ; 
 int /*<<< orphan*/  change_bat_choice (size_t) ; 
 size_t choice_count ; 
 TYPE_2__* choices ; 
 char* default_bat_dir ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  install_bat_choice ; 
 int /*<<< orphan*/  set_bat_text (size_t,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 TYPE_1__* targets ; 
 int /*<<< orphan*/  toggle_bat_choice (size_t) ; 

__attribute__((used)) static void
init_bat_choice(int target)
{
    char	*batpath = targets[target].batpath;
    char	*oldbat = targets[target].oldbat;
    char	*p;
    int		i;

    choices[choice_count].arg = target;
    choices[choice_count].installfunc = install_bat_choice;
    choices[choice_count].active = 1;
    choices[choice_count].text = NULL;	/* will be set below */
    if (oldbat != NULL)
    {
	/* A [g]vim.bat exists: Only choice is to overwrite it or not. */
	choices[choice_count].changefunc = toggle_bat_choice;
	*batpath = NUL;
	toggle_bat_choice(choice_count);
    }
    else
    {
	if (default_bat_dir != NULL)
	    /* Prefer using the same path as an existing .bat file. */
	    strcpy(batpath, default_bat_dir);
	else
	{
	    /* No [g]vim.bat exists: Write it to a directory in $PATH.  Use
	     * $WINDIR by default, if it's empty the first item in $PATH. */
	    p = getenv("WINDIR");
	    if (p != NULL && *p != NUL)
		strcpy(batpath, p);
	    else
	    {
		p = getenv("PATH");
		if (p == NULL || *p == NUL)		/* "cannot happen" */
		    strcpy(batpath, "C:/Windows");
		else
		{
		    i = 0;
		    while (*p != NUL && *p != ';')
			batpath[i++] = *p++;
		    batpath[i] = NUL;
		}
	    }
	}
	add_pathsep(batpath);
	set_bat_text(choice_count, batpath, targets[target].batname);

	choices[choice_count].changefunc = change_bat_choice;
    }
    ++choice_count;
}