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
struct TYPE_2__ {char* text; } ;

/* Variables and functions */
 TYPE_1__* choices ; 
 int install_popup ; 

__attribute__((used)) static void
change_popup_choice(int idx)
{
    if (install_popup == 0)
    {
	choices[idx].text = "Install an entry for Vim in the popup menu for the right\n    mouse button so that you can edit any file with Vim";
	install_popup = 1;
    }
    else
    {
	choices[idx].text = "Do NOT install an entry for Vim in the popup menu for the\n    right mouse button to edit any file with Vim";
	install_popup = 0;
    }
}