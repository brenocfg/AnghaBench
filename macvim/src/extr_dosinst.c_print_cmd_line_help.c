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
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
print_cmd_line_help(void)
{
    printf("Vim installer non-interactive command line arguments:\n");
    printf("\n");
    printf("-create-batfiles  [vim gvim evim view gview vimdiff gvimdiff]\n");
    printf("    Create .bat files for Vim variants in the Windows directory.\n");
    printf("-create-vimrc\n");
    printf("    Create a default _vimrc file if one does not already exist.\n");
    printf("-install-popup\n");
    printf("    Install the Edit-with-Vim context menu entry\n");
    printf("-install-openwith\n");
    printf("    Add Vim to the \"Open With...\" context menu list\n");
#ifdef WIN3264
    printf("-add-start-menu");
    printf("    Add Vim to the start menu\n");
    printf("-install-icons");
    printf("    Create icons for gVim executables on the desktop\n");
#endif
    printf("-create-directories [vim|home]\n");
    printf("    Create runtime directories to drop plugins into; in the $VIM\n");
    printf("    or $HOME directory\n");
#ifdef WIN3264
    printf("-register-OLE");
    printf("    Ignored\n");
#endif
    printf("\n");
}