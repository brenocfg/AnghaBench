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
struct TYPE_2__ {int active; int /*<<< orphan*/ * installfunc; } ;

/* Variables and functions */
 scalar_t__ NUL ; 
 int /*<<< orphan*/  alloc_text (int,char*,scalar_t__*) ; 
 TYPE_1__* choices ; 
 int /*<<< orphan*/ * install_vimrc ; 
 scalar_t__* oldvimrc ; 
 scalar_t__* vimrc ; 

__attribute__((used)) static void
change_vimrc_choice(int idx)
{
    if (choices[idx].installfunc != NULL)
    {
	/* Switch to NOT change or create a vimrc file. */
	if (*oldvimrc != NUL)
	    alloc_text(idx, "Do NOT change startup file %s", oldvimrc);
	else
	    alloc_text(idx, "Do NOT create startup file %s", vimrc);
	choices[idx].installfunc = NULL;
	choices[idx + 1].active = 0;
	choices[idx + 2].active = 0;
	choices[idx + 3].active = 0;
    }
    else
    {
	/* Switch to change or create a vimrc file. */
	if (*oldvimrc != NUL)
	    alloc_text(idx, "Overwrite startup file %s with:", oldvimrc);
	else
	    alloc_text(idx, "Create startup file %s with:", vimrc);
	choices[idx].installfunc = install_vimrc;
	choices[idx + 1].active = 1;
	choices[idx + 2].active = 1;
	choices[idx + 3].active = 1;
    }
}