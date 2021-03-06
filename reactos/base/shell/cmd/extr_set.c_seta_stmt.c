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
typedef  scalar_t__* LPCTSTR ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ _T (char) ; 
 int /*<<< orphan*/  seta_assignment (scalar_t__**,int /*<<< orphan*/ *) ; 
 scalar_t__* skip_ws (scalar_t__*) ; 

__attribute__((used)) static BOOL
seta_stmt(LPCTSTR* p_, INT* result)
{
    LPCTSTR p = *p_;
    INT rval;

    if ( !seta_assignment ( &p, &rval ) )
        return FALSE;
    while ( *p == _T(',') )
    {
        p = skip_ws ( p+1 );

        if ( !seta_assignment ( &p, &rval ) )
            return FALSE;
    }

    *result = rval;
    *p_ = p;
    return TRUE;
}