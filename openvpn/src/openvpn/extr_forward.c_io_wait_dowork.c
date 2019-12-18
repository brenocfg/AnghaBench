#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct event_set_return {int rwflags; scalar_t__ arg; } ;
struct TYPE_8__ {int event_set_status; int /*<<< orphan*/  timeval; int /*<<< orphan*/  event_set; int /*<<< orphan*/  link_socket; int /*<<< orphan*/  inotify_fd; int /*<<< orphan*/  shaper; } ;
struct TYPE_6__ {scalar_t__ mode; scalar_t__ shaper; } ;
struct TYPE_5__ {int /*<<< orphan*/  tuntap; } ;
struct context {TYPE_4__ c2; TYPE_3__* sig; TYPE_2__ options; TYPE_1__ c1; } ;
struct TYPE_7__ {int /*<<< orphan*/  signal_received; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_EVENT_WAIT ; 
 int ES_ERROR ; 
 int ES_TIMEOUT ; 
 unsigned int EVENT_READ ; 
 unsigned int EVENT_WRITE ; 
 unsigned int const IOW_CHECK_RESIDUAL ; 
 unsigned int const IOW_FRAG ; 
 unsigned int const IOW_MBUF ; 
 unsigned int const IOW_READ_LINK ; 
 unsigned int const IOW_READ_TUN ; 
 unsigned int const IOW_READ_TUN_FORCE ; 
 unsigned int const IOW_SHAPER ; 
 unsigned int const IOW_TO_LINK ; 
 unsigned int const IOW_TO_TUN ; 
 unsigned int const IOW_WAIT_SIGNAL ; 
 scalar_t__ MODE_SERVER ; 
 int /*<<< orphan*/  SIZE (struct event_set_return*) ; 
 int SOCKET_READ ; 
 scalar_t__ TO_LINK_FRAG (struct context*) ; 
 scalar_t__ check_debug_level (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_status (int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmsg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  event_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,void*) ; 
 int /*<<< orphan*/  event_reset (int /*<<< orphan*/ ) ; 
 int event_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct event_set_return*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_signal (int /*<<< orphan*/ *) ; 
 scalar_t__ management ; 
 int /*<<< orphan*/  management_socket_set (scalar_t__,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int max_int (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shaper_delay (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shaper_soonest_event (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  show_wait_status (struct context*) ; 
 int /*<<< orphan*/  socket_read_residual (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tun_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_time () ; 
 int /*<<< orphan*/  wait_signal (int /*<<< orphan*/ ,void*) ; 

void
io_wait_dowork(struct context *c, const unsigned int flags)
{
    unsigned int socket = 0;
    unsigned int tuntap = 0;
    struct event_set_return esr[4];

    /* These shifts all depend on EVENT_READ and EVENT_WRITE */
    static int socket_shift = 0;   /* depends on SOCKET_READ and SOCKET_WRITE */
    static int tun_shift = 2;      /* depends on TUN_READ and TUN_WRITE */
    static int err_shift = 4;      /* depends on ES_ERROR */
#ifdef ENABLE_MANAGEMENT
    static int management_shift = 6; /* depends on MANAGEMENT_READ and MANAGEMENT_WRITE */
#endif
#ifdef ENABLE_ASYNC_PUSH
    static int file_shift = 8;     /* listening inotify events */
#endif

    /*
     * Decide what kind of events we want to wait for.
     */
    event_reset(c->c2.event_set);

    /*
     * On win32 we use the keyboard or an event object as a source
     * of asynchronous signals.
     */
    if (flags & IOW_WAIT_SIGNAL)
    {
        wait_signal(c->c2.event_set, (void *)&err_shift);
    }

    /*
     * If outgoing data (for TCP/UDP port) pending, wait for ready-to-send
     * status from TCP/UDP port. Otherwise, wait for incoming data on
     * TUN/TAP device.
     */
    if (flags & IOW_TO_LINK)
    {
        if (flags & IOW_SHAPER)
        {
            /*
             * If sending this packet would put us over our traffic shaping
             * quota, don't send -- instead compute the delay we must wait
             * until it will be OK to send the packet.
             */
#ifdef ENABLE_FEATURE_SHAPER
            int delay = 0;

            /* set traffic shaping delay in microseconds */
            if (c->options.shaper)
            {
                delay = max_int(delay, shaper_delay(&c->c2.shaper));
            }

            if (delay < 1000)
            {
                socket |= EVENT_WRITE;
            }
            else
            {
                shaper_soonest_event(&c->c2.timeval, delay);
            }
#else /* ENABLE_FEATURE_SHAPER */
            socket |= EVENT_WRITE;
#endif /* ENABLE_FEATURE_SHAPER */
        }
        else
        {
            socket |= EVENT_WRITE;
        }
    }
    else if (!((flags & IOW_FRAG) && TO_LINK_FRAG(c)))
    {
        if (flags & IOW_READ_TUN)
        {
            tuntap |= EVENT_READ;
        }
    }

    /*
     * If outgoing data (for TUN/TAP device) pending, wait for ready-to-send status
     * from device.  Otherwise, wait for incoming data on TCP/UDP port.
     */
    if (flags & IOW_TO_TUN)
    {
        tuntap |= EVENT_WRITE;
    }
    else
    {
        if (flags & IOW_READ_LINK)
        {
            socket |= EVENT_READ;
        }
    }

    /*
     * outgoing bcast buffer waiting to be sent?
     */
    if (flags & IOW_MBUF)
    {
        socket |= EVENT_WRITE;
    }

    /*
     * Force wait on TUN input, even if also waiting on TCP/UDP output
     */
    if (flags & IOW_READ_TUN_FORCE)
    {
        tuntap |= EVENT_READ;
    }

    /*
     * Configure event wait based on socket, tuntap flags.
     */
    socket_set(c->c2.link_socket, c->c2.event_set, socket, (void *)&socket_shift, NULL);
    tun_set(c->c1.tuntap, c->c2.event_set, tuntap, (void *)&tun_shift, NULL);

#ifdef ENABLE_MANAGEMENT
    if (management)
    {
        management_socket_set(management, c->c2.event_set, (void *)&management_shift, NULL);
    }
#endif

#ifdef ENABLE_ASYNC_PUSH
    /* arm inotify watcher */
    if (c->options.mode == MODE_SERVER)
    {
        event_ctl(c->c2.event_set, c->c2.inotify_fd, EVENT_READ, (void *)&file_shift);
    }
#endif

    /*
     * Possible scenarios:
     *  (1) tcp/udp port has data available to read
     *  (2) tcp/udp port is ready to accept more data to write
     *  (3) tun dev has data available to read
     *  (4) tun dev is ready to accept more data to write
     *  (5) we received a signal (handler sets signal_received)
     *  (6) timeout (tv) expired
     */

    c->c2.event_set_status = ES_ERROR;

    if (!c->sig->signal_received)
    {
        if (!(flags & IOW_CHECK_RESIDUAL) || !socket_read_residual(c->c2.link_socket))
        {
            int status;

#ifdef ENABLE_DEBUG
            if (check_debug_level(D_EVENT_WAIT))
            {
                show_wait_status(c);
            }
#endif

            /*
             * Wait for something to happen.
             */
            status = event_wait(c->c2.event_set, &c->c2.timeval, esr, SIZE(esr));

            check_status(status, "event_wait", NULL, NULL);

            if (status > 0)
            {
                int i;
                c->c2.event_set_status = 0;
                for (i = 0; i < status; ++i)
                {
                    const struct event_set_return *e = &esr[i];
                    c->c2.event_set_status |= ((e->rwflags & 3) << *((int *)e->arg));
                }
            }
            else if (status == 0)
            {
                c->c2.event_set_status = ES_TIMEOUT;
            }
        }
        else
        {
            c->c2.event_set_status = SOCKET_READ;
        }
    }

    /* 'now' should always be a reasonably up-to-date timestamp */
    update_time();

    /* set signal_received if a signal was received */
    if (c->c2.event_set_status & ES_ERROR)
    {
        get_signal(&c->sig->signal_received);
    }

    dmsg(D_EVENT_WAIT, "I/O WAIT status=0x%04x", c->c2.event_set_status);
}