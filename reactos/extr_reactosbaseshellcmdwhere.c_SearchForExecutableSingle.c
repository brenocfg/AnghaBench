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
typedef  void* TCHAR ;
typedef  void** LPTSTR ;
typedef  void** LPCTSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int CMDLINE_LENGTH ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IsExistingFile (void**) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  TRUE ; 
 void* _T (char) ; 
 void** _tcschr (void**,void*) ; 
 int /*<<< orphan*/  _tcscpy (void**,void**) ; 
 int /*<<< orphan*/  _tcslen (void**) ; 
 int /*<<< orphan*/  _tcsncpy (void**,void**,size_t) ; 
 int /*<<< orphan*/  debugstr_aw (void**) ; 

BOOL
SearchForExecutableSingle (LPCTSTR pFileName, LPTSTR pFullName, LPTSTR pPathExt, LPTSTR pDirectory)
{
    TCHAR  szPathBuffer[CMDLINE_LENGTH], *pszPathEnd;
    LPTSTR s,f;
    /* initialize full name buffer */
    *pFullName = _T('\0');

    TRACE ("SearchForExecutableSingle: \'%s\' in dir: \'%s\'\n",
        debugstr_aw(pFileName), debugstr_aw(pDirectory));

    pszPathEnd = szPathBuffer;
    if (pDirectory != NULL)
    {
        _tcscpy(szPathBuffer, pDirectory);
        pszPathEnd += _tcslen(pszPathEnd);
        *pszPathEnd++ = _T('\\');
    }
    _tcscpy(pszPathEnd, pFileName);
    pszPathEnd += _tcslen(pszPathEnd);

    if (IsExistingFile (szPathBuffer))
    {
        TRACE ("Found: \'%s\'\n", debugstr_aw(szPathBuffer));
        _tcscpy (pFullName, szPathBuffer);
        return TRUE;
    }

    s = pPathExt;
    while (s && *s)
    {
        f = _tcschr (s, _T(';'));

        if (f)
        {
            _tcsncpy (pszPathEnd, s, (size_t)(f-s));
            pszPathEnd[f-s] = _T('\0');
            s = f + 1;
        }
        else
        {
            _tcscpy (pszPathEnd, s);
            s = NULL;
        }

        if (IsExistingFile (szPathBuffer))
        {
            TRACE ("Found: \'%s\'\n", debugstr_aw(szPathBuffer));
            _tcscpy (pFullName, szPathBuffer);
            return TRUE;
        }
    }
    return FALSE;
}