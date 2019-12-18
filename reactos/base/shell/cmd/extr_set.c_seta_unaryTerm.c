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
typedef  int /*<<< orphan*/  LPTSTR ;
typedef  scalar_t__* LPCTSTR ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ConErrResPuts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  PARSE_IDENT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  STRING_EXPECTED_CLOSE_PAREN ; 
 int /*<<< orphan*/  STRING_EXPECTED_NUMBER_OR_VARIABLE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ _T (char) ; 
 scalar_t__ __iscsymf (scalar_t__) ; 
 int /*<<< orphan*/  _tcstol (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ isdigit (scalar_t__) ; 
 int /*<<< orphan*/  seta_identval (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seta_stmt (scalar_t__**,int /*<<< orphan*/ *) ; 
 scalar_t__* skip_ws (scalar_t__*) ; 

__attribute__((used)) static BOOL
seta_unaryTerm(LPCTSTR* p_, INT* result)
{
    LPCTSTR p = *p_;
    if ( *p == _T('(') )
    {
        INT rval;
        p = skip_ws ( p + 1 );
        if ( !seta_stmt ( &p, &rval ) )
            return FALSE;
        if ( *p++ != _T(')') )
        {
            ConErrResPuts ( STRING_EXPECTED_CLOSE_PAREN );
            return FALSE;
        }
        *result = rval;
    }
    else if ( isdigit(*p) )
    {
        *result = _tcstol ( p, (LPTSTR *)&p, 0 );
    }
    else if ( __iscsymf(*p) )
    {
        LPTSTR ident;
        INT identlen;
        PARSE_IDENT(ident,identlen,p);
        *result = seta_identval ( ident );
    }
    else
    {
        ConErrResPuts ( STRING_EXPECTED_NUMBER_OR_VARIABLE );
        return FALSE;
    }
    *p_ = skip_ws ( p );
    return TRUE;
}