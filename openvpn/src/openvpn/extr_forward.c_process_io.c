#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int event_set_status; } ;
struct context {TYPE_1__ c2; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_SIG (struct context*) ; 
 unsigned int const MANAGEMENT_READ ; 
 unsigned int const MANAGEMENT_WRITE ; 
 unsigned int const SOCKET_READ ; 
 unsigned int const SOCKET_WRITE ; 
 unsigned int const TUN_READ ; 
 unsigned int const TUN_WRITE ; 
 int /*<<< orphan*/  management ; 
 int /*<<< orphan*/  management_io (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_incoming_link (struct context*) ; 
 int /*<<< orphan*/  process_incoming_tun (struct context*) ; 
 int /*<<< orphan*/  process_outgoing_link (struct context*) ; 
 int /*<<< orphan*/  process_outgoing_tun (struct context*) ; 
 int /*<<< orphan*/  read_incoming_link (struct context*) ; 
 int /*<<< orphan*/  read_incoming_tun (struct context*) ; 

void
process_io(struct context *c)
{
    const unsigned int status = c->c2.event_set_status;

#ifdef ENABLE_MANAGEMENT
    if (status & (MANAGEMENT_READ|MANAGEMENT_WRITE))
    {
        ASSERT(management);
        management_io(management);
    }
#endif

    /* TCP/UDP port ready to accept write */
    if (status & SOCKET_WRITE)
    {
        process_outgoing_link(c);
    }
    /* TUN device ready to accept write */
    else if (status & TUN_WRITE)
    {
        process_outgoing_tun(c);
    }
    /* Incoming data on TCP/UDP port */
    else if (status & SOCKET_READ)
    {
        read_incoming_link(c);
        if (!IS_SIG(c))
        {
            process_incoming_link(c);
        }
    }
    /* Incoming data on TUN device */
    else if (status & TUN_READ)
    {
        read_incoming_tun(c);
        if (!IS_SIG(c))
        {
            process_incoming_tun(c);
        }
    }
}