#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ LowPart; int /*<<< orphan*/  HighPart; } ;
typedef  scalar_t__* PDWORD ;
typedef  int /*<<< orphan*/  PCWCHAR ;
typedef  scalar_t__ PBYTE ;
typedef  TYPE_1__ LARGE_INTEGER ;
typedef  scalar_t__ HANDLE ;
typedef  scalar_t__ DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int FALSE ; 
 int /*<<< orphan*/  FILE_SHARE_READ ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 scalar_t__ GetFileSizeEx (scalar_t__,TYPE_1__*) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  LocalFree (scalar_t__) ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 
 scalar_t__ ReadFile (scalar_t__,scalar_t__,scalar_t__,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ isBase64InterceptInput ; 
 int kull_m_string_quick_base64_to_Binary (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 

BOOL kull_m_file_readData(PCWCHAR fileName, PBYTE * data, PDWORD lenght)	// for ""little"" files !
{
	BOOL reussite = FALSE;
	DWORD dwBytesReaded;
	LARGE_INTEGER filesize;
	HANDLE hFile = NULL;

	if(isBase64InterceptInput)
	{
		if(!(reussite = kull_m_string_quick_base64_to_Binary(fileName, data, lenght)))
			PRINT_ERROR_AUTO(L"kull_m_string_quick_base64_to_Binary");
	}
	else if((hFile = CreateFile(fileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL)) && hFile != INVALID_HANDLE_VALUE)
	{
		if(GetFileSizeEx(hFile, &filesize) && !filesize.HighPart)
		{
			*lenght = filesize.LowPart;
			if(*data = (PBYTE) LocalAlloc(LPTR, *lenght))
			{
				if(!(reussite = ReadFile(hFile, *data, *lenght, &dwBytesReaded, NULL) && (*lenght == dwBytesReaded)))
					LocalFree(*data);
			}
		}
		CloseHandle(hFile);
	}
	return reussite;
}