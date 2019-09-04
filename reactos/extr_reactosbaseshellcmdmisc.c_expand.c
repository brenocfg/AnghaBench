#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * cFileName; } ;
typedef  TYPE_1__ WIN32_FIND_DATA ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/ * LPTSTR ;
typedef  int /*<<< orphan*/  LPINT ;
typedef  int /*<<< orphan*/ * LPCTSTR ;
typedef  scalar_t__ HANDLE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FindClose (scalar_t__) ; 
 scalar_t__ FindFirstFile (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ FindNextFile (scalar_t__,TYPE_1__*) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  _T (char) ; 
 int /*<<< orphan*/  _tcscat (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _tcscpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int _tcslen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * _tcsrchr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ add_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ***,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmd_alloc (int) ; 
 int /*<<< orphan*/  cmd_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static BOOL expand (LPINT ac, LPTSTR **arg, LPCTSTR pattern)
{
    HANDLE hFind;
    WIN32_FIND_DATA FindData;
    BOOL ok;
    LPCTSTR pathend;
    LPTSTR dirpart, fullname;

    pathend = _tcsrchr (pattern, _T('\\'));
    if (NULL != pathend)
    {
        dirpart = cmd_alloc((pathend - pattern + 2) * sizeof(TCHAR));
        if (!dirpart)
        {
            WARN("Cannot allocate memory for dirpart!\n");
            return FALSE;
        }
        memcpy(dirpart, pattern, pathend - pattern + 1);
        dirpart[pathend - pattern + 1] = _T('\0');
    }
    else
    {
        dirpart = NULL;
    }
    hFind = FindFirstFile (pattern, &FindData);
    if (INVALID_HANDLE_VALUE != hFind)
    {
        do
        {
            if (NULL != dirpart)
            {
                fullname = cmd_alloc((_tcslen(dirpart) + _tcslen(FindData.cFileName) + 1) * sizeof(TCHAR));
                if (!fullname)
                {
                    WARN("Cannot allocate memory for fullname!\n");
                    ok = FALSE;
                }
                else
                {
                    _tcscat (_tcscpy (fullname, dirpart), FindData.cFileName);
                    ok = add_entry(ac, arg, fullname);
                    cmd_free (fullname);
                }
            }
            else
            {
                ok = add_entry(ac, arg, FindData.cFileName);
            }
        } while (FindNextFile (hFind, &FindData) && ok);
        FindClose (hFind);
    }
    else
    {
        ok = add_entry(ac, arg, pattern);
    }

    if (NULL != dirpart)
    {
        cmd_free (dirpart);
    }

    return ok;
}