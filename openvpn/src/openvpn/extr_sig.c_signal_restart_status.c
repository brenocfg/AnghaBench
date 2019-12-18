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
struct signal_info {int signal_received; scalar_t__ signal_text; } ;

/* Variables and functions */
 int OPENVPN_STATE_EXITING ; 
 int OPENVPN_STATE_RECONNECTING ; 
#define  SIGHUP 131 
#define  SIGINT 130 
#define  SIGTERM 129 
#define  SIGUSR1 128 
 scalar_t__ management ; 
 int /*<<< orphan*/  management_set_state (scalar_t__,int,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ signal_name (int,int) ; 

void
signal_restart_status(const struct signal_info *si)
{
#ifdef ENABLE_MANAGEMENT
    if (management)
    {
        int state = -1;
        switch (si->signal_received)
        {
            case SIGINT:
            case SIGTERM:
                state = OPENVPN_STATE_EXITING;
                break;

            case SIGHUP:
            case SIGUSR1:
                state = OPENVPN_STATE_RECONNECTING;
                break;
        }

        if (state >= 0)
        {
            management_set_state(management,
                                 state,
                                 si->signal_text ? si->signal_text : signal_name(si->signal_received, true),
                                 NULL,
                                 NULL,
                                 NULL,
                                 NULL);
        }
    }
#endif /* ifdef ENABLE_MANAGEMENT */
}