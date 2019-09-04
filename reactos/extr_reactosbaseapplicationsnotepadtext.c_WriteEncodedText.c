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
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/ * LPSTR ;
typedef  int /*<<< orphan*/ * LPCWSTR ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int ENCODING ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  CP_UTF8 ; 
#define  ENCODING_ANSI 131 
#define  ENCODING_UTF16BE 130 
#define  ENCODING_UTF16LE 129 
#define  ENCODING_UTF8 128 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 void* WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WriteFile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static BOOL WriteEncodedText(HANDLE hFile, LPCWSTR pszText, DWORD dwTextLen, ENCODING encFile)
{
    LPBYTE pBytes = NULL;
    LPBYTE pAllocBuffer = NULL;
    DWORD dwPos = 0;
    DWORD dwByteCount;
    BYTE buffer[1024];
    UINT iCodePage = 0;
    DWORD dwDummy, i;
    BOOL bSuccess = FALSE;
    int iBufferSize, iRequiredBytes;
    BYTE b;

    while(dwPos < dwTextLen)
    {
        switch(encFile)
        {
            case ENCODING_UTF16LE:
                pBytes = (LPBYTE) &pszText[dwPos];
                dwByteCount = (dwTextLen - dwPos) * sizeof(WCHAR);
                dwPos = dwTextLen;
                break;

            case ENCODING_UTF16BE:
                dwByteCount = (dwTextLen - dwPos) * sizeof(WCHAR);
                if (dwByteCount > sizeof(buffer))
                    dwByteCount = sizeof(buffer);

                memcpy(buffer, &pszText[dwPos], dwByteCount);
                for (i = 0; i < dwByteCount; i += 2)
                {
                    b = buffer[i+0];
                    buffer[i+0] = buffer[i+1];
                    buffer[i+1] = b;
                }
                pBytes = (LPBYTE) &buffer[dwPos];
                dwPos += dwByteCount / sizeof(WCHAR);
                break;

            case ENCODING_ANSI:
            case ENCODING_UTF8:
                if (encFile == ENCODING_ANSI)
                    iCodePage = CP_ACP;
                else if (encFile == ENCODING_UTF8)
                    iCodePage = CP_UTF8;

                iRequiredBytes = WideCharToMultiByte(iCodePage, 0, &pszText[dwPos], dwTextLen - dwPos, NULL, 0, NULL, NULL);
                if (iRequiredBytes <= 0)
                {
                    goto done;
                }
                else if (iRequiredBytes < sizeof(buffer))
                {
                    pBytes = buffer;
                    iBufferSize = sizeof(buffer);
                }
                else
                {
                    pAllocBuffer = (LPBYTE) HeapAlloc(GetProcessHeap(), 0, iRequiredBytes);
                    if (!pAllocBuffer)
                        return FALSE;
                    pBytes = pAllocBuffer;
                    iBufferSize = iRequiredBytes;
                }

                dwByteCount = WideCharToMultiByte(iCodePage, 0, &pszText[dwPos], dwTextLen - dwPos, (LPSTR) pBytes, iBufferSize, NULL, NULL);
                if (!dwByteCount)
                    goto done;

                dwPos = dwTextLen;
                break;

            default:
                goto done;
        }

        if (!WriteFile(hFile, pBytes, dwByteCount, &dwDummy, NULL))
            goto done;

        /* free the buffer, if we have allocated one */
        if (pAllocBuffer)
        {
            HeapFree(GetProcessHeap(), 0, pAllocBuffer);
            pAllocBuffer = NULL;
        }
    }
    bSuccess = TRUE;

done:
    if (pAllocBuffer)
        HeapFree(GetProcessHeap(), 0, pAllocBuffer);
    return bSuccess;
}