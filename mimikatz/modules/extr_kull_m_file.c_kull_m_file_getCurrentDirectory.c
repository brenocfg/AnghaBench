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
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int GetCurrentDirectory (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 

BOOL kull_m_file_getCurrentDirectory(wchar_t ** ppDirName)
{
	BOOL reussite = FALSE;
	DWORD tailleRequise = GetCurrentDirectory(0, NULL);
	if(*ppDirName = (wchar_t *) LocalAlloc(LPTR, tailleRequise * sizeof(wchar_t)))
		if(!(reussite = (tailleRequise > 0 && (GetCurrentDirectory(tailleRequise, *ppDirName) == tailleRequise - 1))))
			LocalFree(*ppDirName);

	return reussite;
}