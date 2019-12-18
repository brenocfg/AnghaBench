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
typedef  int TCHAR ;
typedef  int* LPCTSTR ;
typedef  int INT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _T (char*) ; 
 scalar_t__ _tcschr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  seta_unaryTerm (int**,int*) ; 
 int* skip_ws (int*) ; 

__attribute__((used)) static BOOL
seta_mulTerm(LPCTSTR* p_, INT* result)
{
    LPCTSTR p = *p_;
    TCHAR op = 0;
    INT rval;
    if ( _tcschr(_T("!~-"),*p) )
    {
        op = *p;
        p = skip_ws ( p + 1 );
    }
    if ( !seta_unaryTerm ( &p, &rval ) )
        return FALSE;
    switch ( op )
    {
    case '!':
        rval = !rval;
        break;
    case '~':
        rval = ~rval;
        break;
    case '-':
        rval = -rval;
        break;
    }

    *result = rval;
    *p_ = p;
    return TRUE;
}