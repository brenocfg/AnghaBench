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
typedef  int /*<<< orphan*/ * LPCTSTR ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ConErrResPuts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ConOutPrintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  STRING_SYNTAX_COMMAND_INCORRECT ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  bc ; 
 int /*<<< orphan*/  seta_stmt (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL
seta_eval(LPCTSTR p)
{
    INT rval;
    if ( !*p )
    {
        ConErrResPuts ( STRING_SYNTAX_COMMAND_INCORRECT );
        return FALSE;
    }
    if ( !seta_stmt ( &p, &rval ) )
        return FALSE;
    if ( !bc )
        ConOutPrintf ( _T("%i"), rval );
    return TRUE;
}