#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  tuntap; } ;
struct TYPE_14__ {int /*<<< orphan*/  len; } ;
struct TYPE_12__ {TYPE_5__ buf; int /*<<< orphan*/  n_trunc_tun_read; int /*<<< orphan*/  frame; TYPE_1__* buffers; } ;
struct TYPE_11__ {int restart_sleep_seconds; } ;
struct context {TYPE_4__ c1; TYPE_3__ c2; TYPE_2__ persist; } ;
struct TYPE_10__ {TYPE_5__ read_tun_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BLEN (TYPE_5__*) ; 
 int /*<<< orphan*/  BPTR (TYPE_5__*) ; 
 int /*<<< orphan*/  FRAME_HEADROOM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAX_RW_SIZE_TUN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_INFO ; 
 int /*<<< orphan*/  PERF_READ_IN_TUN ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  TUNNEL_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buf_init (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buf_safe (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_status (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipv4_packet_size_verify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  perf_pop () ; 
 int /*<<< orphan*/  perf_push (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_tun (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_tun_buffered (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  register_signal (struct context*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ tuntap_abort (int /*<<< orphan*/ ) ; 
 scalar_t__ tuntap_stop (int /*<<< orphan*/ ) ; 

void
read_incoming_tun(struct context *c)
{
    /*
     * Setup for read() call on TUN/TAP device.
     */
    /*ASSERT (!c->c2.to_link.len);*/

    perf_push(PERF_READ_IN_TUN);

    c->c2.buf = c->c2.buffers->read_tun_buf;
#ifdef _WIN32
    read_tun_buffered(c->c1.tuntap, &c->c2.buf);
#else
    ASSERT(buf_init(&c->c2.buf, FRAME_HEADROOM(&c->c2.frame)));
    ASSERT(buf_safe(&c->c2.buf, MAX_RW_SIZE_TUN(&c->c2.frame)));
    c->c2.buf.len = read_tun(c->c1.tuntap, BPTR(&c->c2.buf), MAX_RW_SIZE_TUN(&c->c2.frame));
#endif

#ifdef PACKET_TRUNCATION_CHECK
    ipv4_packet_size_verify(BPTR(&c->c2.buf),
                            BLEN(&c->c2.buf),
                            TUNNEL_TYPE(c->c1.tuntap),
                            "READ_TUN",
                            &c->c2.n_trunc_tun_read);
#endif

    /* Was TUN/TAP interface stopped? */
    if (tuntap_stop(c->c2.buf.len))
    {
        register_signal(c, SIGTERM, "tun-stop");
        msg(M_INFO, "TUN/TAP interface has been stopped, exiting");
        perf_pop();
        return;
    }

    /* Was TUN/TAP I/O operation aborted? */
    if (tuntap_abort(c->c2.buf.len))
    {
        register_signal(c, SIGHUP, "tun-abort");
        c->persist.restart_sleep_seconds = 10;
        msg(M_INFO, "TUN/TAP I/O operation aborted, restarting");
        perf_pop();
        return;
    }

    /* Check the status return from read() */
    check_status(c->c2.buf.len, "read from TUN/TAP", NULL, c->c1.tuntap);

    perf_pop();
}