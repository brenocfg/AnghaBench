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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  PCWCHAR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  PathCanonicalize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PathCombine (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ PathIsRelative (int /*<<< orphan*/ ) ; 
 scalar_t__ kull_m_file_getCurrentDirectory (int /*<<< orphan*/ **) ; 

BOOL kull_m_file_getAbsolutePathOf(PCWCHAR thisData, wchar_t ** reponse)
{
	BOOL reussite = FALSE;
	wchar_t *monRep;
	*reponse = (wchar_t *) LocalAlloc(LPTR, MAX_PATH * sizeof(wchar_t));

	if(PathIsRelative(thisData))
	{
		if(kull_m_file_getCurrentDirectory(&monRep))
		{
			reussite = (PathCombine(*reponse , monRep, thisData) != NULL);
			LocalFree(monRep);
		}
	}
	else reussite = PathCanonicalize(*reponse, thisData);

	if(!reussite)
		LocalFree(*reponse);

	return reussite;
}