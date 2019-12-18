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
typedef  int /*<<< orphan*/  Portal ;

/* Variables and functions */
 int /*<<< orphan*/  CreatePortal (char*,int,int) ; 
 int /*<<< orphan*/ * GetPortalByName (char*) ; 
 int MAX_PORTALNAME_LEN ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 

Portal
CreateNewPortal(void)
{
	static unsigned int unnamed_portal_count = 0;

	char		portalname[MAX_PORTALNAME_LEN];

	/* Select a nonconflicting name */
	for (;;)
	{
		unnamed_portal_count++;
		sprintf(portalname, "<unnamed portal %u>", unnamed_portal_count);
		if (GetPortalByName(portalname) == NULL)
			break;
	}

	return CreatePortal(portalname, false, false);
}