#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  win_T ;
struct TYPE_5__ {TYPE_3__* tab; } ;
typedef  TYPE_1__ TabPageObject ;
struct TYPE_6__ {int /*<<< orphan*/ * tp_firstwin; } ;

/* Variables and functions */
 scalar_t__ CheckTabPage (TYPE_1__*) ; 
 TYPE_3__* curtab ; 
 int /*<<< orphan*/ * firstwin ; 

__attribute__((used)) static win_T *
get_firstwin(TabPageObject *tabObject)
{
    if (tabObject)
    {
	if (CheckTabPage(tabObject))
	    return NULL;
	/* For current tab window.c does not bother to set or update tp_firstwin
	 */
	else if (tabObject->tab == curtab)
	    return firstwin;
	else
	    return tabObject->tab->tp_firstwin;
    }
    else
	return firstwin;
}