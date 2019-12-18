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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/ * LPCTSTR ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int FORMAT_MESSAGE_ARGUMENT_ARRAY ; 
 int FORMAT_MESSAGE_FROM_SYSTEM ; 
 int FORMAT_MESSAGE_IGNORE_INSERTS ; 
 scalar_t__ FormatMessage (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_ERR ; 
 int /*<<< orphan*/  MsgToEventLog (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TEXT (char*) ; 

__attribute__((used)) static void
BlockDNSErrHandler(DWORD err, const char *msg)
{
    TCHAR buf[256];
    LPCTSTR err_str;

    if (!err)
    {
        return;
    }

    err_str = TEXT("Unknown Win32 Error");

    if (FormatMessage(FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_SYSTEM
                      | FORMAT_MESSAGE_ARGUMENT_ARRAY,
                      NULL, err, 0, buf, sizeof(buf), NULL))
    {
        err_str = buf;
    }

#ifdef UNICODE
    MsgToEventLog(M_ERR, L"%S (status = %lu): %s", msg, err, err_str);
#else
    MsgToEventLog(M_ERR, "%s (status = %lu): %s", msg, err, err_str);
#endif

}