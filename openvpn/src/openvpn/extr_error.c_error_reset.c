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
 int /*<<< orphan*/  OPENVPN_DEBUG_FILE ; 
 int /*<<< orphan*/  OPENVPN_EXIT_STATUS_CANNOT_OPEN_DEBUG_FILE ; 
 void* OPENVPN_MSG_FP ; 
 void* default_err ; 
 void* default_out ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int machine_readable_output ; 
 int /*<<< orphan*/ * msgfp ; 
 scalar_t__ mute_category ; 
 scalar_t__ mute_count ; 
 scalar_t__ mute_cutoff ; 
 int /*<<< orphan*/  openvpn_exit (int /*<<< orphan*/ ) ; 
 int std_redir ; 
 int suppress_timestamps ; 
 int use_syslog ; 
 int x_debug_level ; 

void
error_reset(void)
{
    use_syslog = std_redir = false;
    suppress_timestamps = false;
    machine_readable_output = false;
    x_debug_level = 1;
    mute_cutoff = 0;
    mute_count = 0;
    mute_category = 0;
    default_out = OPENVPN_MSG_FP;
    default_err = OPENVPN_MSG_FP;

#ifdef OPENVPN_DEBUG_COMMAND_LINE
    msgfp = fopen(OPENVPN_DEBUG_FILE, "w");
    if (!msgfp)
    {
        openvpn_exit(OPENVPN_EXIT_STATUS_CANNOT_OPEN_DEBUG_FILE); /* exit point */
    }
#else  /* ifdef OPENVPN_DEBUG_COMMAND_LINE */
    msgfp = NULL;
#endif
}