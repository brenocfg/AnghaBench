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
typedef  int /*<<< orphan*/ * Portal ;

/* Variables and functions */
 scalar_t__ PointerIsValid (char const*) ; 
 int /*<<< orphan*/  PortalHashTableLookup (char const*,int /*<<< orphan*/ *) ; 

Portal
GetPortalByName(const char *name)
{
	Portal		portal;

	if (PointerIsValid(name))
		PortalHashTableLookup(name, portal);
	else
		portal = NULL;

	return portal;
}