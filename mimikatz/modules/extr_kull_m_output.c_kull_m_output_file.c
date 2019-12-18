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
typedef  scalar_t__ PCWCHAR ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/ * _wfopen (scalar_t__,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * logfile ; 

BOOL kull_m_output_file(PCWCHAR file)
{
	BOOL status = FALSE;
	FILE * newlog = NULL;

	if(file)
#pragma warning(push)
#pragma warning(disable:4996)
		newlog = _wfopen(file, L"a"); // XP does not like _wfopen_s
#pragma warning(pop)
	if(newlog || !file)
	{
		if(logfile)
			fclose(logfile);
		logfile = newlog;
	}
	return (!file || (file && logfile));
}