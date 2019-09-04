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
typedef  int /*<<< orphan*/  lval ;
typedef  int TCHAR ;
typedef  scalar_t__* LPCTSTR ;
typedef  int INT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ConErrResPuts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  STRING_INVALID_OPERAND ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _T (char*) ; 
 scalar_t__ _tcschr (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  seta_logShiftTerm (scalar_t__**,int*) ; 
 scalar_t__* skip_ws (scalar_t__*) ; 

__attribute__((used)) static BOOL
seta_bitAndTerm(LPCTSTR* p_, INT* result)
{
    LPCTSTR p = *p_;
    INT lval;
    if ( !seta_logShiftTerm ( &p, &lval ) )
        return FALSE;
    while ( *p && _tcschr(_T("<>"),*p) && p[0] == p[1] )
    {
        INT rval;
        TCHAR op = *p;

        p = skip_ws ( p+2 );

        if ( !seta_logShiftTerm ( &p, &rval ) )
            return FALSE;

        switch ( op )
        {
        case '<':
        {
            /* Shift left has to be a positive number, 0-31 otherwise 0 is returned,
             * which differs from the compiler (for example gcc) so being explicit. */
            if (rval < 0 || rval >= (8 * sizeof(lval)))
                lval = 0;
            else
                lval <<= rval;
            break;
        }
        case '>':
            lval >>= rval;
            break;
        default:
            ConErrResPuts ( STRING_INVALID_OPERAND );
            return FALSE;
        }
    }

    *result = lval;
    *p_ = p;
    return TRUE;
}