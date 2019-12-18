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
typedef  int /*<<< orphan*/  wchar_t ;
struct nk_text_edit {int dummy; } ;
typedef  int /*<<< orphan*/  nk_handle ;
typedef  int SIZE_T ;
typedef  scalar_t__ LPCWSTR ;
typedef  scalar_t__ HGLOBAL ;

/* Variables and functions */
 int /*<<< orphan*/  CF_UNICODETEXT ; 
 int /*<<< orphan*/  CP_UTF8 ; 
 int /*<<< orphan*/  CloseClipboard () ; 
 scalar_t__ GetClipboardData (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalLock (scalar_t__) ; 
 int GlobalSize (scalar_t__) ; 
 int /*<<< orphan*/  GlobalUnlock (scalar_t__) ; 
 scalar_t__ IsClipboardFormatAvailable (int /*<<< orphan*/ ) ; 
 scalar_t__ OpenClipboard (int /*<<< orphan*/ *) ; 
 int WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  nk_textedit_paste (struct nk_text_edit*,char*,int) ; 

__attribute__((used)) static void
nk_gdi_clipboard_paste(nk_handle usr, struct nk_text_edit *edit)
{
    (void)usr;
    if (IsClipboardFormatAvailable(CF_UNICODETEXT) && OpenClipboard(NULL))
    {
        HGLOBAL mem = GetClipboardData(CF_UNICODETEXT); 
        if (mem)
        {
            SIZE_T size = GlobalSize(mem) - 1;
            if (size)
            {
                LPCWSTR wstr = (LPCWSTR)GlobalLock(mem);
                if (wstr) 
                {
                    int utf8size = WideCharToMultiByte(CP_UTF8, 0, wstr, (int)(size / sizeof(wchar_t)), NULL, 0, NULL, NULL);
                    if (utf8size)
                    {
                        char* utf8 = (char*)malloc(utf8size);
                        if (utf8)
                        {
                            WideCharToMultiByte(CP_UTF8, 0, wstr, (int)(size / sizeof(wchar_t)), utf8, utf8size, NULL, NULL);
                            nk_textedit_paste(edit, utf8, utf8size);
                            free(utf8);
                        }
                    }
                    GlobalUnlock(mem); 
                }
            }
        }
        CloseClipboard();
    }
}