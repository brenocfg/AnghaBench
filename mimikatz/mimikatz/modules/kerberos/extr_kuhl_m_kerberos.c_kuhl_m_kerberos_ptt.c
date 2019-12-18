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
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  PathFindFileName (int /*<<< orphan*/ *) ; 
 scalar_t__ PathIsDirectory (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  kprintf (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kuhl_m_kerberos_ptt_directory (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kull_m_file_Find (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *),int /*<<< orphan*/ *) ; 

NTSTATUS kuhl_m_kerberos_ptt(int argc, wchar_t * argv[])
{
	int i;
	for(i = 0; i < argc; i++)
	{
		if(PathIsDirectory(argv[i]))
		{
			kprintf(L"* Directory: \'%s\'\n", argv[i]);
			kull_m_file_Find(argv[i], L"*.kirbi", FALSE, 0, FALSE, kuhl_m_kerberos_ptt_directory, NULL);
		}
		else kuhl_m_kerberos_ptt_directory(0, argv[i], PathFindFileName(argv[i]), NULL);
	}
	return STATUS_SUCCESS;
}