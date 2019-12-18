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
 int ZONEC_MAXFIELDS ; 
 int ZONEC_MINFIELDS ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ) ; 
 int inzsub (char**,int,int) ; 

__attribute__((used)) static bool
inzcont(char **fields, int nfields)
{
	if (nfields < ZONEC_MINFIELDS || nfields > ZONEC_MAXFIELDS)
	{
		error(_("wrong number of fields on Zone continuation line"));
		return false;
	}
	return inzsub(fields, nfields, true);
}