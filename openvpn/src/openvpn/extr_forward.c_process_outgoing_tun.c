#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct gc_arena {int dummy; } ;
struct TYPE_15__ {scalar_t__ len; } ;
struct TYPE_13__ {int tun_write_bytes; TYPE_4__ to_tun; int /*<<< orphan*/  frame; int /*<<< orphan*/  n_trunc_tun_write; scalar_t__ log_rw; } ;
struct TYPE_12__ {TYPE_3__* tuntap; } ;
struct context {TYPE_2__ c2; TYPE_1__ c1; } ;
struct TYPE_14__ {int /*<<< orphan*/  actual_name; } ;

/* Variables and functions */
 int BLEN (TYPE_4__*) ; 
 int /*<<< orphan*/  BPTR (TYPE_4__*) ; 
 int /*<<< orphan*/  D_LINK_ERRORS ; 
 int /*<<< orphan*/  D_TUN_RW ; 
 scalar_t__ MAX_RW_SIZE_TUN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PERF_PROC_OUT_TUN ; 
 int PIPV4_CLIENT_NAT ; 
 int PIPV4_EXTRACT_DHCP_ROUTER ; 
 int PIP_MSSFIX ; 
 int PIP_OUTGOING ; 
 int /*<<< orphan*/  TUNNEL_TYPE (TYPE_3__*) ; 
 int /*<<< orphan*/  buf_reset (TYPE_4__*) ; 
 int /*<<< orphan*/  check_status (int,char*,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  dmsg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 struct gc_arena gc_new () ; 
 int /*<<< orphan*/  ipv4_packet_size_verify (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,...) ; 
 int /*<<< orphan*/  perf_pop () ; 
 int /*<<< orphan*/  perf_push (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_ip_header (struct context*,int,TYPE_4__*) ; 
 int /*<<< orphan*/  register_activity (struct context*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int write_tun (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int write_tun_buffered (TYPE_3__*,TYPE_4__*) ; 

void
process_outgoing_tun(struct context *c)
{
    struct gc_arena gc = gc_new();

    /*
     * Set up for write() call to TUN/TAP
     * device.
     */
    if (c->c2.to_tun.len <= 0)
    {
        return;
    }

    perf_push(PERF_PROC_OUT_TUN);

    /*
     * The --mssfix option requires
     * us to examine the IP header (IPv4 or IPv6).
     */
    process_ip_header(c,
                      PIP_MSSFIX | PIPV4_EXTRACT_DHCP_ROUTER | PIPV4_CLIENT_NAT | PIP_OUTGOING,
                      &c->c2.to_tun);

    if (c->c2.to_tun.len <= MAX_RW_SIZE_TUN(&c->c2.frame))
    {
        /*
         * Write to TUN/TAP device.
         */
        int size;

#ifdef LOG_RW
        if (c->c2.log_rw)
        {
            fprintf(stderr, "w");
        }
#endif
        dmsg(D_TUN_RW, "TUN WRITE [%d]", BLEN(&c->c2.to_tun));

#ifdef PACKET_TRUNCATION_CHECK
        ipv4_packet_size_verify(BPTR(&c->c2.to_tun),
                                BLEN(&c->c2.to_tun),
                                TUNNEL_TYPE(c->c1.tuntap),
                                "WRITE_TUN",
                                &c->c2.n_trunc_tun_write);
#endif

#ifdef _WIN32
        size = write_tun_buffered(c->c1.tuntap, &c->c2.to_tun);
#else
        size = write_tun(c->c1.tuntap, BPTR(&c->c2.to_tun), BLEN(&c->c2.to_tun));
#endif

        if (size > 0)
        {
            c->c2.tun_write_bytes += size;
        }
        check_status(size, "write to TUN/TAP", NULL, c->c1.tuntap);

        /* check written packet size */
        if (size > 0)
        {
            /* Did we write a different size packet than we intended? */
            if (size != BLEN(&c->c2.to_tun))
            {
                msg(D_LINK_ERRORS,
                    "TUN/TAP packet was destructively fragmented on write to %s (tried=%d,actual=%d)",
                    c->c1.tuntap->actual_name,
                    BLEN(&c->c2.to_tun),
                    size);
            }

            /* indicate activity regarding --inactive parameter */
            register_activity(c, size);
        }
    }
    else
    {
        /*
         * This should never happen, probably indicates some kind
         * of MTU mismatch.
         */
        msg(D_LINK_ERRORS, "tun packet too large on write (tried=%d,max=%d)",
            c->c2.to_tun.len,
            MAX_RW_SIZE_TUN(&c->c2.frame));
    }

    buf_reset(&c->c2.to_tun);

    perf_pop();
    gc_free(&gc);
}