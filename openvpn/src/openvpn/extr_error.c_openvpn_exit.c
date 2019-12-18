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
 int const OPENVPN_EXIT_STATUS_ERROR ; 
 int const OPENVPN_EXIT_STATUS_GOOD ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  close_syslog () ; 
 int /*<<< orphan*/  exit (int const) ; 
 int /*<<< orphan*/  forked ; 
 int /*<<< orphan*/  mstats_close () ; 
 int /*<<< orphan*/  perf_output_results () ; 
 int /*<<< orphan*/  plugin_abort () ; 
 scalar_t__ port_share ; 
 int /*<<< orphan*/  port_share_abort (scalar_t__) ; 
 int /*<<< orphan*/  tun_abort () ; 
 int /*<<< orphan*/  uninit_win32 () ; 

void
openvpn_exit(const int status)
{
    if (!forked)
    {
        tun_abort();

#ifdef _WIN32
        uninit_win32();
#endif

        close_syslog();

#ifdef ENABLE_PLUGIN
        plugin_abort();
#endif

#if PORT_SHARE
        if (port_share)
        {
            port_share_abort(port_share);
        }
#endif

#ifdef ENABLE_MEMSTATS
        mstats_close();
#endif

#ifdef ABORT_ON_ERROR
        if (status == OPENVPN_EXIT_STATUS_ERROR)
        {
            abort();
        }
#endif

        if (status == OPENVPN_EXIT_STATUS_GOOD)
        {
            perf_output_results();
        }
    }

    exit(status);
}