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
struct se_set {int maxfd; int /*<<< orphan*/ ** args; int /*<<< orphan*/  writefds; int /*<<< orphan*/  readfds; int /*<<< orphan*/  fast; } ;
struct event_set {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  D_EVENT_WAIT ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmsg (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
se_reset(struct event_set *es)
{
    struct se_set *ses = (struct se_set *) es;
    int i;
    ASSERT(ses->fast);

    dmsg(D_EVENT_WAIT, "SE_RESET");

    FD_ZERO(&ses->readfds);
    FD_ZERO(&ses->writefds);
    for (i = 0; i <= ses->maxfd; ++i)
    {
        ses->args[i] = NULL;
    }
    ses->maxfd = -1;
}