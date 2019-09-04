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
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/ * LPTSTR ;
typedef  int* LPINT ;
typedef  int /*<<< orphan*/  LPCTSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  _tcscpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int _tcslen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cmd_alloc (int) ; 
 int /*<<< orphan*/  cmd_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** cmd_realloc (int /*<<< orphan*/ **,int) ; 

BOOL add_entry (LPINT ac, LPTSTR **arg, LPCTSTR entry)
{
    LPTSTR q;
    LPTSTR *oldarg;

    q = cmd_alloc ((_tcslen(entry) + 1) * sizeof (TCHAR));
    if (!q)
    {
        WARN("Cannot allocate memory for q!\n");
        return FALSE;
    }

    _tcscpy (q, entry);
    oldarg = *arg;
    *arg = cmd_realloc (oldarg, (*ac + 2) * sizeof (LPTSTR));
    if (!*arg)
    {
        WARN("Cannot reallocate memory for arg!\n");
        *arg = oldarg;
        cmd_free (q);
        return FALSE;
    }

    /* save new entry */
    (*arg)[*ac] = q;
    (*arg)[++(*ac)] = NULL;

    return TRUE;
}