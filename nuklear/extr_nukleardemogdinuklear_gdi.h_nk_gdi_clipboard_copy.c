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
typedef  scalar_t__ wchar_t ;
typedef  int /*<<< orphan*/  nk_handle ;
typedef  scalar_t__ HGLOBAL ;

/* Variables and functions */
 int /*<<< orphan*/  CF_UNICODETEXT ; 
 int /*<<< orphan*/  CP_UTF8 ; 
 int /*<<< orphan*/  CloseClipboard () ; 
 int /*<<< orphan*/  GMEM_MOVEABLE ; 
 int /*<<< orphan*/  GlobalAlloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ GlobalLock (scalar_t__) ; 
 int /*<<< orphan*/  GlobalUnlock (scalar_t__) ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,scalar_t__*,int) ; 
 scalar_t__ OpenClipboard (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetClipboardData (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
nk_gdi_clipboard_copy(nk_handle usr, const char *text, int len)
{
    if (OpenClipboard(NULL))
    {
        int wsize = MultiByteToWideChar(CP_UTF8, 0, text, len, NULL, 0);
        if (wsize)
        {
            HGLOBAL mem = (HGLOBAL)GlobalAlloc(GMEM_MOVEABLE, (wsize + 1) * sizeof(wchar_t));
            if (mem)
            {
                wchar_t* wstr = (wchar_t*)GlobalLock(mem);
                if (wstr)
                {
                    MultiByteToWideChar(CP_UTF8, 0, text, len, wstr, wsize);
                    wstr[wsize] = 0;
                    GlobalUnlock(mem); 

                    SetClipboardData(CF_UNICODETEXT, mem); 
                }
            }
        }
        CloseClipboard();
    }
}