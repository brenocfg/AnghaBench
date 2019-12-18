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
struct se_set {size_t capacity; int /*<<< orphan*/ ** args; int /*<<< orphan*/  writefds; int /*<<< orphan*/  readfds; int /*<<< orphan*/  fast; } ;
struct event_set {int dummy; } ;
typedef  size_t event_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  D_EVENT_ERRORS ; 
 int /*<<< orphan*/  D_EVENT_WAIT ; 
 int /*<<< orphan*/  FD_CLR (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmsg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
se_del(struct event_set *es, event_t event)
{
    struct se_set *ses = (struct se_set *) es;
    ASSERT(!ses->fast);

    dmsg(D_EVENT_WAIT, "SE_DEL ev=%d", (int)event);

    if (event >= 0 && event < ses->capacity)
    {
        FD_CLR(event, &ses->readfds);
        FD_CLR(event, &ses->writefds);
        ses->args[event] = NULL;
    }
    else
    {
        msg(D_EVENT_ERRORS, "Error: select/se_del: too many I/O wait events");
    }
    return;
}