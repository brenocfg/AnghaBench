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
struct context {int signal_received; scalar_t__ source; char* signal_text; struct context* sig; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct context*) ; 
 unsigned int CC_GC_FREE ; 
 unsigned int CC_HARD_USR1_TO_HUP ; 
 unsigned int CC_NO_CLOSE ; 
 unsigned int CC_USR1_TO_HUP ; 
 int SIGHUP ; 
 int SIGUSR1 ; 
 scalar_t__ SIG_SOURCE_HARD ; 
 int /*<<< orphan*/  close_instance (struct context*) ; 
 int /*<<< orphan*/  context_gc_free (struct context*) ; 

void
close_context(struct context *c, int sig, unsigned int flags)
{
    ASSERT(c);
    ASSERT(c->sig);

    if (sig >= 0)
    {
        c->sig->signal_received = sig;
    }

    if (c->sig->signal_received == SIGUSR1)
    {
        if ((flags & CC_USR1_TO_HUP)
            || (c->sig->source == SIG_SOURCE_HARD && (flags & CC_HARD_USR1_TO_HUP)))
        {
            c->sig->signal_received = SIGHUP;
            c->sig->signal_text = "close_context usr1 to hup";
        }
    }

    if (!(flags & CC_NO_CLOSE))
    {
        close_instance(c);
    }

    if (flags & CC_GC_FREE)
    {
        context_gc_free(c);
    }
}