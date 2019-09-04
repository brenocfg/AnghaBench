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
 int FALSE ; 
 scalar_t__ STRCMP (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int TRUE ; 
 int /*<<< orphan*/ * last_sourcing_name ; 
 int /*<<< orphan*/ * sourcing_name ; 

__attribute__((used)) static int
other_sourcing_name()
{
    if (sourcing_name != NULL)
    {
	if (last_sourcing_name != NULL)
	    return STRCMP(sourcing_name, last_sourcing_name) != 0;
	return TRUE;
    }
    return FALSE;
}