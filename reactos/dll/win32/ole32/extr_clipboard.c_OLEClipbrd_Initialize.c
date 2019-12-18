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
struct TYPE_5__ {int /*<<< orphan*/  marshal_data; int /*<<< orphan*/ * cached_enum; int /*<<< orphan*/ * src_data; int /*<<< orphan*/ * window; int /*<<< orphan*/ * latest_snapshot; } ;
typedef  TYPE_1__ ole_clipbrd ;
typedef  int /*<<< orphan*/  HGLOBAL ;

/* Variables and functions */
 int /*<<< orphan*/  CreateStreamOnHGlobal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int GMEM_DDESHARE ; 
 int GMEM_MOVEABLE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  GlobalAlloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalFree (int /*<<< orphan*/ ) ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  register_clipboard_formats () ; 
 TYPE_1__* theOleClipboard ; 

void OLEClipbrd_Initialize(void)
{
    register_clipboard_formats();

    if ( !theOleClipboard )
    {
        ole_clipbrd* clipbrd;
        HGLOBAL h;

        TRACE("()\n");

        clipbrd = HeapAlloc( GetProcessHeap(), 0, sizeof(*clipbrd) );
        if (!clipbrd) return;

        clipbrd->latest_snapshot = NULL;
        clipbrd->window = NULL;
        clipbrd->src_data = NULL;
        clipbrd->cached_enum = NULL;

        h = GlobalAlloc(GMEM_DDESHARE | GMEM_MOVEABLE, 0);
        if(!h)
        {
            HeapFree(GetProcessHeap(), 0, clipbrd);
            return;
        }

        if(FAILED(CreateStreamOnHGlobal(h, TRUE, &clipbrd->marshal_data)))
        {
            GlobalFree(h);
            HeapFree(GetProcessHeap(), 0, clipbrd);
            return;
        }

        theOleClipboard = clipbrd;
    }
}