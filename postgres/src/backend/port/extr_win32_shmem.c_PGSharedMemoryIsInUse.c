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
typedef  int /*<<< orphan*/ * HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FILE_MAP_READ ; 
 char* GetSharedMemName () ; 
 int /*<<< orphan*/ * OpenFileMapping (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 

bool
PGSharedMemoryIsInUse(unsigned long id1, unsigned long id2)
{
	char	   *szShareMem;
	HANDLE		hmap;

	szShareMem = GetSharedMemName();

	hmap = OpenFileMapping(FILE_MAP_READ, FALSE, szShareMem);

	free(szShareMem);

	if (hmap == NULL)
		return false;

	CloseHandle(hmap);
	return true;
}