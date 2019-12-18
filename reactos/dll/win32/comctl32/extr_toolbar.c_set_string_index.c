#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_4__ {int iString; } ;
typedef  TYPE_1__ TBUTTON_INFO ;
typedef  int INT_PTR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IS_INTRESOURCE (int) ; 
 int /*<<< orphan*/  Str_SetPtrAtoW (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  Str_SetPtrW (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ TOOLBAR_ButtonHasString (TYPE_1__*) ; 

__attribute__((used)) static void set_string_index( TBUTTON_INFO *btn, INT_PTR str, BOOL unicode )
{
    if (!IS_INTRESOURCE( str ) && str != -1)
    {
        if (!TOOLBAR_ButtonHasString( btn )) btn->iString = 0;

        if (unicode)
            Str_SetPtrW( (WCHAR **)&btn->iString, (WCHAR *)str );
        else
            Str_SetPtrAtoW( (WCHAR **)&btn->iString, (char *)str );
    }
    else
    {
        if (TOOLBAR_ButtonHasString( btn )) Free( (WCHAR *)btn->iString );

        btn->iString  = str;
    }
}