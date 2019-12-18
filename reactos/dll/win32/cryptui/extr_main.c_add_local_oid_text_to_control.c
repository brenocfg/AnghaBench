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
struct OIDToString {int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  parFmt ;
typedef  char WCHAR ;
struct TYPE_3__ {int cbSize; int dxStartIndent; int /*<<< orphan*/  dwMask; } ;
typedef  TYPE_1__ PARAFORMAT2 ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  char* LPCSTR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAX_STRING_LEN ; 
 int MY_INDENT ; 
 int /*<<< orphan*/  PFM_STARTINDENT ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  add_text_with_paraformat_to_control (int /*<<< orphan*/ ,char*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  add_unformatted_text_to_control (int /*<<< orphan*/ ,char*,int) ; 
 struct OIDToString* findSupportedOID (char*) ; 
 int /*<<< orphan*/  hInstance ; 
 int /*<<< orphan*/  lstrcpynW (char*,char*,int) ; 
 int lstrlenW (char*) ; 
 int strlen (char*) ; 
 char* wmemchr (char*,char,int) ; 

__attribute__((used)) static void add_local_oid_text_to_control(HWND text, LPCSTR oid)
{
    struct OIDToString *entry;
    WCHAR nl = '\n';
    PARAFORMAT2 parFmt;

    parFmt.cbSize = sizeof(parFmt);
    parFmt.dwMask = PFM_STARTINDENT;
    parFmt.dxStartIndent = MY_INDENT * 3;
    if ((entry = findSupportedOID(oid)))
    {
        WCHAR *str, *linebreak, *ptr;
        BOOL multiline = FALSE;
        int len;

        len = LoadStringW(hInstance, entry->id, (LPWSTR)&str, 0);
        ptr = str;
        do {
            if ((linebreak = wmemchr(ptr, '\n', len)))
            {
                WCHAR copy[MAX_STRING_LEN];

                multiline = TRUE;
                /* The source string contains a newline, which the richedit
                 * control won't find since it's interpreted as a paragraph
                 * break.  Therefore copy up to the newline.  lstrcpynW always
                 * NULL-terminates, so pass one more than the length of the
                 * source line so the copy includes the entire line and the
                 * NULL-terminator.
                 */
                lstrcpynW(copy, ptr, linebreak - ptr + 1);
                add_text_with_paraformat_to_control(text, copy,
                 linebreak - ptr, &parFmt);
                ptr = linebreak + 1;
                add_unformatted_text_to_control(text, &nl, 1);
            }
            else if (multiline && *ptr)
            {
                /* Add the last line */
                add_text_with_paraformat_to_control(text, ptr,
                 len - (ptr - str), &parFmt);
                add_unformatted_text_to_control(text, &nl, 1);
            }
        } while (linebreak);
        if (!multiline)
        {
            add_text_with_paraformat_to_control(text, str, len, &parFmt);
            add_unformatted_text_to_control(text, &nl, 1);
        }
    }
    else
    {
        WCHAR *oidW = HeapAlloc(GetProcessHeap(), 0,
         (strlen(oid) + 1) * sizeof(WCHAR));

        if (oidW)
        {
            LPCSTR src;
            WCHAR *dst;

            for (src = oid, dst = oidW; *src; src++, dst++)
                *dst = *src;
            *dst = 0;
            add_text_with_paraformat_to_control(text, oidW, lstrlenW(oidW),
             &parFmt);
            add_unformatted_text_to_control(text, &nl, 1);
            HeapFree(GetProcessHeap(), 0, oidW);
        }
    }
}