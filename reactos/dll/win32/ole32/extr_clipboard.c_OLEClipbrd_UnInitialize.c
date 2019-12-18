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
struct TYPE_5__ {int /*<<< orphan*/  marshal_data; scalar_t__ window; scalar_t__ src_data; } ;
typedef  TYPE_1__ ole_clipbrd ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  HINSTANCE ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyWindow (scalar_t__) ; 
 int /*<<< orphan*/  GetModuleHandleW (char const*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  IDataObject_AddRef (scalar_t__) ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  UnregisterClassW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clipbrd_wndclass ; 
 int /*<<< orphan*/  set_src_dataobject (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* theOleClipboard ; 

void OLEClipbrd_UnInitialize(void)
{
    ole_clipbrd *clipbrd = theOleClipboard;

    TRACE("()\n");

    if ( clipbrd )
    {
        static const WCHAR ole32W[] = {'o','l','e','3','2',0};
        HINSTANCE hinst = GetModuleHandleW(ole32W);

        /* OleUninitialize() does not release the reference to the dataobject, so
           take an additional reference here.  This reference is then leaked. */
        if (clipbrd->src_data)
        {
            IDataObject_AddRef(clipbrd->src_data);
            set_src_dataobject(clipbrd, NULL);
        }

        if ( clipbrd->window )
        {
            DestroyWindow(clipbrd->window);
            UnregisterClassW( clipbrd_wndclass, hinst );
        }

        IStream_Release(clipbrd->marshal_data);
        HeapFree(GetProcessHeap(), 0, clipbrd);
        theOleClipboard = NULL;
    }
}