#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {int /*<<< orphan*/  hWndLBox; int /*<<< orphan*/  hWndEdit; } ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  TYPE_1__* LPHEADCOMBO ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int INT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GetWindowTextW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int LB_ERR ; 
 int /*<<< orphan*/  LB_FINDSTRING ; 
 int /*<<< orphan*/  LB_SETCARETINDEX ; 
 int /*<<< orphan*/  LB_SETCURSEL ; 
 int /*<<< orphan*/  LB_SETTOPINDEX ; 
 int SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 int /*<<< orphan*/  WM_GETTEXTLENGTH ; 
 int /*<<< orphan*/ * heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static INT CBUpdateLBox( LPHEADCOMBO lphc, BOOL bSelect )
{
   INT	length, idx;
   LPWSTR pText = NULL;

   idx = LB_ERR;
   length = SendMessageW( lphc->hWndEdit, WM_GETTEXTLENGTH, 0, 0 );

    if (length > 0)
        pText = heap_alloc((length + 1) * sizeof(WCHAR));

   TRACE("\t edit text length %i\n", length );

   if( pText )
   {
       GetWindowTextW( lphc->hWndEdit, pText, length + 1);
       idx = SendMessageW(lphc->hWndLBox, LB_FINDSTRING, -1, (LPARAM)pText);
       heap_free( pText );
   }

   SendMessageW(lphc->hWndLBox, LB_SETCURSEL, bSelect ? idx : -1, 0);

   /* probably superfluous but Windows sends this too */
   SendMessageW(lphc->hWndLBox, LB_SETCARETINDEX, idx < 0 ? 0 : idx, 0);
   SendMessageW(lphc->hWndLBox, LB_SETTOPINDEX, idx < 0 ? 0 : idx, 0);

   return idx;
}