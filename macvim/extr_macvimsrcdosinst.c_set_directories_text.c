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
 int /*<<< orphan*/  alloc_text (int,char*,char*) ; 
 int vimfiles_dir_choice ; 
 char** vimfiles_dir_choices ; 
 scalar_t__ vimfiles_dir_none ; 

__attribute__((used)) static void
set_directories_text(int idx)
{
    if (vimfiles_dir_choice == (int)vimfiles_dir_none)
	alloc_text(idx, "Do NOT create plugin directories%s", "");
    else
	alloc_text(idx, "Create plugin directories: %s",
				   vimfiles_dir_choices[vimfiles_dir_choice]);
}