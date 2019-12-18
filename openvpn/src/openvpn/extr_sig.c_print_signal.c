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
struct signal_info {char* signal_text; int source; int signal_received; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
#define  SIGHUP 134 
#define  SIGINT 133 
#define  SIGTERM 132 
#define  SIGUSR1 131 
#define  SIG_SOURCE_CONNECTION_FAILED 130 
#define  SIG_SOURCE_HARD 129 
#define  SIG_SOURCE_SOFT 128 
 int /*<<< orphan*/  msg (int,char*,...) ; 
 int /*<<< orphan*/  signal_name (int,int) ; 

void
print_signal(const struct signal_info *si, const char *title, int msglevel)
{
    if (si)
    {
        const char *type = (si->signal_text ? si->signal_text : "");
        const char *t = (title ? title : "process");
        const char *hs = NULL;
        switch (si->source)
        {
            case SIG_SOURCE_SOFT:
                hs = "soft";
                break;

            case SIG_SOURCE_HARD:
                hs = "hard";
                break;

            case SIG_SOURCE_CONNECTION_FAILED:
                hs = "connection failed(soft)";
                break;

            default:
                ASSERT(0);
        }

        switch (si->signal_received)
        {
            case SIGINT:
            case SIGTERM:
                msg(msglevel, "%s[%s,%s] received, %s exiting",
                    signal_name(si->signal_received, true), hs, type, t);
                break;

            case SIGHUP:
            case SIGUSR1:
                msg(msglevel, "%s[%s,%s] received, %s restarting",
                    signal_name(si->signal_received, true), hs, type, t);
                break;

            default:
                msg(msglevel, "Unknown signal %d [%s,%s] received by %s", si->signal_received, hs, type, t);
                break;
        }
    }
    else
    {
        msg(msglevel, "Unknown signal received");
    }
}