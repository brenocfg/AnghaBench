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
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  WriteConsoleW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mp_from_utf8 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ *) ; 
 size_t wcslen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void write_console_text(HANDLE wstream, char *buf)
{
    wchar_t *out = mp_from_utf8(NULL, buf);
    size_t out_len = wcslen(out);
    WriteConsoleW(wstream, out, out_len, NULL, NULL);
    talloc_free(out);
}