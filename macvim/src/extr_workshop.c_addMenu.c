#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cbuf ;
struct TYPE_5__ {int /*<<< orphan*/ * verb; int /*<<< orphan*/ * accel; int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ MenuMap ;

/* Variables and functions */
 int BUFSIZ ; 
 int MENU_INC ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  coloncmd (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* menuMap ; 
 int menuMapMax ; 
 int menuMapSize ; 
 TYPE_1__* realloc (TYPE_1__*,int) ; 
 int /*<<< orphan*/ * strdup (char*) ; 
 int /*<<< orphan*/  vim_snprintf (char*,int,char*,char*,char*) ; 
 scalar_t__ workshopHotKeysEnabled ; 

__attribute__((used)) static void
addMenu(
	char		*menu,		/* menu name */
	char		*accel,		/* accelerator text (optional) */
	char		*verb)		/* WorkShop action-verb */
{
    MenuMap		*newMap;
    char		 cbuf[BUFSIZ];

    if (menuMapSize >= menuMapMax)
    {
	newMap = realloc(menuMap,
		sizeof(MenuMap) * (menuMapMax + MENU_INC));
	if (newMap != NULL)
	{
	    menuMap = newMap;
	    menuMapMax += MENU_INC;
	}
    }
    if (menuMapSize < menuMapMax)
    {
	menuMap[menuMapSize].name = strdup(menu);
	menuMap[menuMapSize].accel = accel && *accel ? strdup(accel) : NULL;
	menuMap[menuMapSize++].verb = strdup(verb);
	if (accel && workshopHotKeysEnabled)
	{
	    vim_snprintf(cbuf, sizeof(cbuf),
					"map %s :wsverb %s<CR>", accel, verb);
	    coloncmd(cbuf, TRUE);
	}
    }
}