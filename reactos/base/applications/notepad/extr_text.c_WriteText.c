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
typedef  char WCHAR ;
typedef  char* LPCWSTR ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  ENCODING ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ENCODING_ANSI ; 
#define  EOLN_CR 130 
#define  EOLN_CRLF 129 
#define  EOLN_LF 128 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WriteEncodedText (int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ ) ; 

BOOL WriteText(HANDLE hFile, LPCWSTR pszText, DWORD dwTextLen, ENCODING encFile, int iEoln)
{
    WCHAR wcBom;
    LPCWSTR pszLF = L"\n";
    DWORD dwPos, dwNext;

    /* Write the proper byte order marks if not ANSI */
    if (encFile != ENCODING_ANSI)
    {
        wcBom = 0xFEFF;
        if (!WriteEncodedText(hFile, &wcBom, 1, encFile))
            return FALSE;
    }

    dwPos = 0;

    /* pszText eoln are always \r\n */

    do
    {
        /* Find the next eoln */
        dwNext = dwPos;
        while(dwNext < dwTextLen)
        {
            if (pszText[dwNext] == '\r' && pszText[dwNext + 1] == '\n')
                break;
            dwNext++;
        }

        if (dwNext != dwTextLen)
        {
            switch (iEoln)
            {
            case EOLN_LF:
                /* Write text (without eoln) */
                if (!WriteEncodedText(hFile, &pszText[dwPos], dwNext - dwPos, encFile))
                    return FALSE;
                /* Write eoln */
                if (!WriteEncodedText(hFile, pszLF, 1, encFile))
                    return FALSE;
                break;
            case EOLN_CR:
                /* Write text (including \r as eoln) */
                if (!WriteEncodedText(hFile, &pszText[dwPos], dwNext - dwPos + 1, encFile))
                    return FALSE;
                break;
            case EOLN_CRLF:
                /* Write text (including \r\n as eoln) */
                if (!WriteEncodedText(hFile, &pszText[dwPos], dwNext - dwPos + 2, encFile))
                    return FALSE;
                break;
            default:
                return FALSE;
            }
        }
        else
        {
            /* Write text (without eoln, since this is the end of the file) */
            if (!WriteEncodedText(hFile, &pszText[dwPos], dwNext - dwPos, encFile))
                return FALSE;
        }

        /* Skip \r\n */
        dwPos = dwNext + 2;
    }
    while (dwPos < dwTextLen);

    return TRUE;
}