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
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_5__ {int /*<<< orphan*/  start; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ bstr ;

/* Variables and functions */
 int /*<<< orphan*/  bstr0 (char*) ; 
 int /*<<< orphan*/  bstr_xappend (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bstr_xappend_asprintf (int /*<<< orphan*/ *,TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/ * mp_from_utf8 (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_arg (TYPE_1__*,char*) ; 

__attribute__((used)) static wchar_t *write_cmdline(void *ctx, char **argv)
{
    // argv[0] should always be quoted. Otherwise, arguments may be interpreted
    // as part of the program name. Also, it can't contain escape sequences.
    bstr cmdline = {0};
    bstr_xappend_asprintf(NULL, &cmdline, "\"%s\"", argv[0]);

    for (int i = 1; argv[i]; i++) {
        bstr_xappend(NULL, &cmdline, bstr0(" "));
        write_arg(&cmdline, argv[i]);
    }

    wchar_t *wcmdline = mp_from_utf8(ctx, cmdline.start);
    talloc_free(cmdline.start);
    return wcmdline;
}