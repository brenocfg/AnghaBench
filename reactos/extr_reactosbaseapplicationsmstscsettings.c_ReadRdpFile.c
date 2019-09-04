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
typedef  scalar_t__* LPWSTR ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int GetFileSize (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ ReadFile (scalar_t__,scalar_t__*,int,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static LPWSTR
ReadRdpFile(HANDLE hFile)
{
    LPWSTR lpBuffer = NULL;
    DWORD BytesToRead, BytesRead;
    BOOL bRes;

    if (hFile)
    {
        BytesToRead = GetFileSize(hFile, NULL);
        if (BytesToRead)
        {
            lpBuffer = HeapAlloc(GetProcessHeap(),
                                 0,
                                 BytesToRead + 2);
            if (lpBuffer)
            {
                bRes = ReadFile(hFile,
                                lpBuffer,
                                BytesToRead,
                                &BytesRead,
                                NULL);
                if (bRes)
                {
                    lpBuffer[BytesRead / 2] = 0;
                }
                else
                {
                    HeapFree(GetProcessHeap(),
                             0,
                             lpBuffer);

                    lpBuffer = NULL;
                }
            }
        }
    }

    return lpBuffer;
}