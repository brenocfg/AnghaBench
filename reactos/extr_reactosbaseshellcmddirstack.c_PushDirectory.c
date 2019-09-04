#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  szPath; struct TYPE_5__* prev; struct TYPE_5__* next; } ;
typedef  int /*<<< orphan*/  LPTSTR ;
typedef  TYPE_1__* LPDIRENTRY ;
typedef  int INT ;

/* Variables and functions */
 int /*<<< orphan*/  DIRENTRY ; 
 int /*<<< orphan*/  FIELD_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  _tcscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int _tcslen (int /*<<< orphan*/ ) ; 
 TYPE_1__* cmd_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error_out_of_memory () ; 
 TYPE_1__* lpStackBottom ; 
 TYPE_1__* lpStackTop ; 
 int nErrorLevel ; 
 int /*<<< orphan*/  nStackDepth ; 
 int /*<<< orphan*/ * szPath ; 

__attribute__((used)) static INT
PushDirectory (LPTSTR pszPath)
{
    LPDIRENTRY lpDir = cmd_alloc(FIELD_OFFSET(DIRENTRY, szPath[_tcslen(pszPath) + 1]));
    if (!lpDir)
    {
        WARN("Cannot allocate memory for lpDir\n");
        error_out_of_memory();
        return -1;
    }

    lpDir->prev = NULL;
    lpDir->next = lpStackTop;
    if (lpStackTop == NULL)
        lpStackBottom = lpDir;
    else
        lpStackTop->prev = lpDir;
    lpStackTop = lpDir;

    _tcscpy(lpDir->szPath, pszPath);

    nStackDepth++;

    return nErrorLevel = 0;
}