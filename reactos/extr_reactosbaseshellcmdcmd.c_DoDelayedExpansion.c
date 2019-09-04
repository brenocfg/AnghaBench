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
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/ * LPTSTR ;

/* Variables and functions */
 int CMDLINE_LENGTH ; 
 int /*<<< orphan*/  SubstituteForVars (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SubstituteVars (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _T (char) ; 
 int /*<<< orphan*/  _tcschr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bDelayedExpansion ; 
 int /*<<< orphan*/ * cmd_dup (int /*<<< orphan*/ *) ; 

LPTSTR
DoDelayedExpansion(LPTSTR Line)
{
    TCHAR Buf1[CMDLINE_LENGTH];
    TCHAR Buf2[CMDLINE_LENGTH];

    /* First, substitute FOR variables */
    if (!SubstituteForVars(Line, Buf1))
        return NULL;

    if (!bDelayedExpansion || !_tcschr(Buf1, _T('!')))
        return cmd_dup(Buf1);

    /* FIXME: Delayed substitutions actually aren't quite the same as
     * immediate substitutions. In particular, it's possible to escape
     * the exclamation point using ^. */
    if (!SubstituteVars(Buf1, Buf2, _T('!')))
        return NULL;
    return cmd_dup(Buf2);
}