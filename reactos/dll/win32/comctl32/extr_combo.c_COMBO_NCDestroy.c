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
struct TYPE_5__ {int /*<<< orphan*/  self; scalar_t__ hWndLBox; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_1__ HEADCOMBO ;

/* Variables and functions */
 scalar_t__ CBS_SIMPLE ; 
 scalar_t__ CB_GETTYPE (TYPE_1__*) ; 
 int /*<<< orphan*/  DestroyWindow (scalar_t__) ; 
 int /*<<< orphan*/  SetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_free (TYPE_1__*) ; 

__attribute__((used)) static LRESULT COMBO_NCDestroy( HEADCOMBO *lphc )
{
    if (lphc)
    {
        TRACE("[%p]: freeing storage\n", lphc->self);

        if ( (CB_GETTYPE(lphc) != CBS_SIMPLE) && lphc->hWndLBox )
            DestroyWindow( lphc->hWndLBox );

        SetWindowLongPtrW( lphc->self, 0, 0 );
        heap_free( lphc );
    }

    return 0;
}