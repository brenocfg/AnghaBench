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
struct TYPE_2__ {int /*<<< orphan*/  (* installfunc ) (int) ;scalar_t__ active; } ;

/* Variables and functions */
 int choice_count ; 
 TYPE_1__* choices ; 
 scalar_t__ has_gvim ; 
 int /*<<< orphan*/  install_OLE_register () ; 
 scalar_t__ install_openwith ; 
 scalar_t__ install_popup ; 
 int /*<<< orphan*/  install_registry () ; 
 scalar_t__ interactive ; 
 scalar_t__ need_uninstall_entry ; 
 int /*<<< orphan*/  stub1 (int) ; 

__attribute__((used)) static void
install(void)
{
    int		i;

    /* Install the selected choices. */
    for (i = 0; i < choice_count; ++i)
	if (choices[i].installfunc != NULL && choices[i].active)
	    (choices[i].installfunc)(i);

    /* Add some entries to the registry, if needed. */
    if (install_popup
	    || install_openwith
	    || (need_uninstall_entry && interactive)
	    || !interactive)
	install_registry();

#ifdef WIN3264
    /* Register gvim with OLE. */
    if (has_gvim)
	install_OLE_register();
#endif
}