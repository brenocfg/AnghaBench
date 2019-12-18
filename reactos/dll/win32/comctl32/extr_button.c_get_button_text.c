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
struct TYPE_3__ {int /*<<< orphan*/  hwnd; } ;
typedef  int INT ;
typedef  TYPE_1__ BUTTON_INFO ;

/* Variables and functions */
 int GetWindowTextLengthW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWindowTextW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * heap_alloc (int) ; 

__attribute__((used)) static inline WCHAR *get_button_text( const BUTTON_INFO *infoPtr )
{
    INT len = GetWindowTextLengthW( infoPtr->hwnd );
    WCHAR *buffer = heap_alloc( (len + 1) * sizeof(WCHAR) );
    if (buffer)
        GetWindowTextW( infoPtr->hwnd, buffer, len + 1 );
    return buffer;
}