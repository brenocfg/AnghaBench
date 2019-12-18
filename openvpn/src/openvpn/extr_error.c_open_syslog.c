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

/* Variables and functions */
 int /*<<< orphan*/  LOG_OPENVPN ; 
 int /*<<< orphan*/  LOG_PID ; 
 int /*<<< orphan*/  M_WARN ; 
 char const* PACKAGE ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msgfp ; 
 int /*<<< orphan*/  openlog (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgmname_syslog ; 
 int /*<<< orphan*/  set_std_files_to_null (int) ; 
 int /*<<< orphan*/  std_redir ; 
 int /*<<< orphan*/  string_alloc (char const*,int /*<<< orphan*/ *) ; 
 int use_syslog ; 

void
open_syslog(const char *pgmname, bool stdio_to_null)
{
#if SYSLOG_CAPABILITY
    if (!msgfp && !std_redir)
    {
        if (!use_syslog)
        {
            pgmname_syslog = string_alloc(pgmname ? pgmname : PACKAGE, NULL);
            openlog(pgmname_syslog, LOG_PID, LOG_OPENVPN);
            use_syslog = true;

            /* Better idea: somehow pipe stdout/stderr output to msg() */
            if (stdio_to_null)
            {
                set_std_files_to_null(false);
            }
        }
    }
#else  /* if SYSLOG_CAPABILITY */
    msg(M_WARN, "Warning on use of --daemon/--inetd: this operating system lacks daemon logging features, therefore when I become a daemon, I won't be able to log status or error messages");
#endif
}