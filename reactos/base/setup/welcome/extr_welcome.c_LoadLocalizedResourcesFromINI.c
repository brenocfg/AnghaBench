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
struct TYPE_3__ {scalar_t__* szArgs; scalar_t__* szDesc; scalar_t__* szTitle; scalar_t__* szText; scalar_t__* szCommand; } ;
typedef  TYPE_1__ TOPIC ;
typedef  scalar_t__ TCHAR ;
typedef  scalar_t__* LPTSTR ;
typedef  int /*<<< orphan*/  LCID ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAYSIZE (scalar_t__*) ; 
 TYPE_1__* AddNewTopicEx (scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int BUFFER_SIZE ; 
 int /*<<< orphan*/  FALSE ; 
 int FILE_ATTRIBUTE_DIRECTORY ; 
 int GetFileAttributes (scalar_t__*) ; 
 scalar_t__ GetLocaleName (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int GetPrivateProfileSectionNames (scalar_t__*,int,scalar_t__*) ; 
 int /*<<< orphan*/  GetPrivateProfileString (scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int INVALID_FILE_ATTRIBUTES ; 
 int LOCALE_NAME_MAX_LENGTH ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  StringCchCopy (scalar_t__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  StringCchPrintf (scalar_t__*,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 scalar_t__* TEXT (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TranslateEscapes (scalar_t__*) ; 
 scalar_t__ _tcslen (scalar_t__*) ; 
 scalar_t__ _tcsnicmp (scalar_t__*,scalar_t__*,int) ; 
 scalar_t__* szAppTitle ; 
 scalar_t__* szDefaultDesc ; 
 scalar_t__* szDefaultTitle ; 

__attribute__((used)) static BOOL
LoadLocalizedResourcesFromINI(LCID Locale, LPTSTR lpResPath)
{
    DWORD dwRet;
    DWORD dwAttribs;
    DWORD dwSize;
    TCHAR szBuffer[LOCALE_NAME_MAX_LENGTH];
    TCHAR szIniPath[MAX_PATH];
    LPTSTR lpszSections = NULL, lpszSection = NULL;
    LPTSTR lpszCommand, lpszAction;
    TOPIC newTopic, *pTopic;

    /* Retrieve the locale name (on which the INI file name is based) */
    dwRet = (DWORD)GetLocaleName(Locale, szBuffer, ARRAYSIZE(szBuffer));
    if (!dwRet)
    {
        /* Fall back to english (US) */
        StringCchCopy(szBuffer, ARRAYSIZE(szBuffer), TEXT("en-US"));
    }

    /* Build the INI file name */
    StringCchPrintf(szIniPath, ARRAYSIZE(szIniPath),
                    TEXT("%s\\%s.ini"), lpResPath, szBuffer);

    /* Verify that the file exists, otherwise fall back to english (US) */
    dwAttribs = GetFileAttributes(szIniPath);
    if ((dwAttribs == INVALID_FILE_ATTRIBUTES) ||
        (dwAttribs & FILE_ATTRIBUTE_DIRECTORY))
    {
        StringCchCopy(szBuffer, ARRAYSIZE(szBuffer), TEXT("en-US"));

        StringCchPrintf(szIniPath, ARRAYSIZE(szIniPath),
                        TEXT("%s\\%s.ini"), lpResPath, szBuffer);
    }

    /* Verify that the file exists, otherwise fall back to internal (localized) resource */
    dwAttribs = GetFileAttributes(szIniPath);
    if ((dwAttribs == INVALID_FILE_ATTRIBUTES) ||
        (dwAttribs & FILE_ATTRIBUTE_DIRECTORY))
    {
        return FALSE; // For localized resources, see the general function.
    }

    /* Try to load the default localized strings */
    GetPrivateProfileString(TEXT("Defaults"), TEXT("AppTitle"), TEXT("ReactOS - Welcome") /* default */,
                            szAppTitle, ARRAYSIZE(szAppTitle), szIniPath);
    GetPrivateProfileString(TEXT("Defaults"), TEXT("DefaultTopicTitle"), TEXT("") /* default */,
                            szDefaultTitle, ARRAYSIZE(szDefaultTitle), szIniPath);
    if (!GetPrivateProfileString(TEXT("Defaults"), TEXT("DefaultTopicDescription"), TEXT("") /* default */,
                                 szDefaultDesc, ARRAYSIZE(szDefaultDesc), szIniPath))
    {
        *szDefaultDesc = 0;
    }
    else
    {
        TranslateEscapes(szDefaultDesc);
    }

    /* Allocate a buffer big enough to hold all the section names */
    for (dwSize = BUFFER_SIZE; ; dwSize += BUFFER_SIZE)
    {
        lpszSections = HeapAlloc(GetProcessHeap(), 0, dwSize * sizeof(TCHAR));
        if (!lpszSections)
            return TRUE; // FIXME!
        dwRet = GetPrivateProfileSectionNames(lpszSections, dwSize, szIniPath);
        if (dwRet < dwSize - 2)
            break;
        HeapFree(GetProcessHeap(), 0, lpszSections);
    }

    /* Loop over the sections and load the topics */
    lpszSection = lpszSections;
    for (; lpszSection && *lpszSection; lpszSection += (_tcslen(lpszSection) + 1))
    {
        /* Ignore everything that is not a topic */
        if (_tcsnicmp(lpszSection, TEXT("Topic"), 5) != 0)
            continue;

        lpszCommand = NULL, lpszAction = NULL;

        /* Retrieve the information */
        GetPrivateProfileString(lpszSection, TEXT("MenuText"), TEXT("") /* default */,
                                newTopic.szText, ARRAYSIZE(newTopic.szText), szIniPath);
        GetPrivateProfileString(lpszSection, TEXT("Title"), TEXT("") /* default */,
                                newTopic.szTitle, ARRAYSIZE(newTopic.szTitle), szIniPath);
        GetPrivateProfileString(lpszSection, TEXT("Description"), TEXT("") /* default */,
                                newTopic.szDesc, ARRAYSIZE(newTopic.szDesc), szIniPath);

        GetPrivateProfileString(lpszSection, TEXT("ConfigCommand"), TEXT("") /* default */,
                                newTopic.szCommand, ARRAYSIZE(newTopic.szCommand), szIniPath);

        /* Only care about command arguments if we actually have a command */
        if (*newTopic.szCommand)
        {
            lpszCommand = newTopic.szCommand;
            GetPrivateProfileString(lpszSection, TEXT("ConfigArgs"), TEXT("") /* default */,
                                    newTopic.szArgs, ARRAYSIZE(newTopic.szArgs), szIniPath);
        }
        /* Only care about custom actions if we actually don't have a command */
        else // if (!*newTopic.szCommand)
        {
            lpszAction = newTopic.szCommand;
            GetPrivateProfileString(lpszSection, TEXT("Action"), TEXT("") /* default */,
                                    newTopic.szCommand, ARRAYSIZE(newTopic.szCommand), szIniPath);
        }

        /* Allocate a new topic */
        pTopic = AddNewTopicEx(newTopic.szText,
                               newTopic.szTitle,
                               newTopic.szDesc,
                               lpszCommand,
                               newTopic.szArgs,
                               lpszAction);
        if (!pTopic)
            break; // Cannot reallocate more
    }

    HeapFree(GetProcessHeap(), 0, lpszSections);

    return TRUE;
}