#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct udp_pcb {int dummy; } ;
struct rtc_timeval {scalar_t__ tv_sec; int /*<<< orphan*/  tv_usec; } ;
struct pbuf {int len; int /*<<< orphan*/  payload; } ;
struct ip_addr {scalar_t__ addr; } ;
struct TYPE_16__ {int sec; scalar_t__ frac; } ;
typedef  TYPE_5__ ntp_timestamp_t ;
struct TYPE_15__ {scalar_t__ sec; scalar_t__ frac; } ;
struct TYPE_14__ {int sec; int frac; } ;
struct TYPE_13__ {int sec; int frac; } ;
struct TYPE_17__ {int LI; int root_dispersion; int root_delay; TYPE_4__ origin; int /*<<< orphan*/  stratum; TYPE_3__ xmit; TYPE_2__ recv; int /*<<< orphan*/  refid; } ;
typedef  TYPE_6__ ntp_frame_t ;
typedef  int /*<<< orphan*/  ntp ;
struct TYPE_18__ {scalar_t__ addr; } ;
typedef  TYPE_7__ ip_addr_t ;
typedef  int int64_t ;
struct TYPE_20__ {scalar_t__ addr; } ;
struct TYPE_12__ {scalar_t__ sec; scalar_t__ frac; } ;
struct TYPE_19__ {size_t server_pos; int kodbits; int last_server_pos; int /*<<< orphan*/  timer; TYPE_1__ cookie; struct udp_pcb* pcb; } ;

/* Variables and functions */
 int /*<<< orphan*/  NTP_ANYCAST_ADDR (TYPE_7__*) ; 
 scalar_t__ US_TO_FRAC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_zero_base_timeofday (struct rtc_timeval*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,char*,int) ; 
 int ntohl (int) ; 
 int /*<<< orphan*/  os_memcpy (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_timer_disarm (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pbuf_free (struct pbuf*) ; 
 int pending_LI ; 
 int /*<<< orphan*/  record_result (int,struct ip_addr*,int,int /*<<< orphan*/ ,int,int,int,int,int) ; 
 int /*<<< orphan*/  rtctime_gettimeofday (struct rtc_timeval*) ; 
 TYPE_9__* serverp ; 
 int /*<<< orphan*/  sntp_dbg (char*,...) ; 
 int /*<<< orphan*/  sntp_dosend () ; 
 TYPE_8__* state ; 
 int system_get_time () ; 
 int const the_offset ; 
 int /*<<< orphan*/  udp_remove (struct udp_pcb*) ; 
 int /*<<< orphan*/  update_offset () ; 

__attribute__((used)) static void on_recv (void *arg, struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint16_t port)
{
  (void)port;
#ifdef LUA_USE_MODULES_RTCTIME
  // Ideally this would be done when we receive the packet....
  struct rtc_timeval tv;

  rtctime_gettimeofday (&tv);
  if (tv.tv_sec == 0) {
    get_zero_base_timeofday(&tv);
  }
#endif
  sntp_dbg("sntp: on_recv\n");

  if (!state || state->pcb != pcb)
  {
    // "impossible", but don't leak if it did happen somehow...
    udp_remove (pcb);
    pbuf_free (p);
    return;
  }

  if (!p)
    return;

  if (p->len < sizeof (ntp_frame_t))
  {
    pbuf_free (p);
    return; // not an ntp frame, ignore
  }

  // make sure we have an aligned copy to work from
  ntp_frame_t ntp;
  os_memcpy (&ntp, p->payload, sizeof (ntp));
  pbuf_free (p);
  sntp_dbg("sntp: transmit timestamp: %u, %u\n", ntp.xmit.sec, ntp.xmit.frac);

  // sanity checks before we touch our clocks
  ip_addr_t anycast;
  NTP_ANYCAST_ADDR(&anycast);
  if (serverp[state->server_pos].addr != anycast.addr && serverp[state->server_pos].addr != addr->addr)
    return; // unknown sender, ignore

  if (ntp.origin.sec  != state->cookie.sec ||
      ntp.origin.frac != state->cookie.frac)
    return; // unsolicited message, ignore

  if (ntp.LI == 3) {
    if (memcmp(&ntp.refid, "DENY", 4) == 0) {
      // KoD packet
      if (state->kodbits & (1 << state->server_pos)) {
        // Oh dear -- two packets rxed. Kill this entry
        serverp[state->server_pos].addr = 0;
      } else {
        state->kodbits |= (1 << state->server_pos);
      }
    }
    return; // server clock not synchronized (why did it even respond?!)
  }

  // clear kod -- we got a good packet back
  state->kodbits &= ~(1 << state->server_pos);

  os_timer_disarm(&state->timer);

  if (ntp.LI) {
    pending_LI = ntp.LI;
  }

  update_offset();

  ntp.origin.sec  = ntohl (ntp.origin.sec);
  ntp.origin.frac = ntohl (ntp.origin.frac);
  ntp.recv.sec  = ntohl (ntp.recv.sec);
  ntp.recv.frac = ntohl (ntp.recv.frac);
  ntp.xmit.sec  = ntohl (ntp.xmit.sec);
  ntp.xmit.frac = ntohl (ntp.xmit.frac);

  const uint64_t MICROSECONDS = 1000000ull;
  const uint32_t NTP_TO_UNIX_EPOCH = 2208988800ul;

  uint32_t root_maxerr = ntohl(ntp.root_dispersion) + ntohl(ntp.root_delay) / 2;

  bool same_as_last = state->server_pos == state->last_server_pos;

  // if we have rtctime, do higher resolution delta calc, else just use
  // the transmit timestamp
#ifdef LUA_USE_MODULES_RTCTIME
  ntp_timestamp_t dest;
  dest.sec = tv.tv_sec + NTP_TO_UNIX_EPOCH - the_offset;
  dest.frac = US_TO_FRAC(tv.tv_usec);

  uint64_t ntp_recv = (((uint64_t) ntp.recv.sec) << 32) + (uint64_t) ntp.recv.frac;
  uint64_t ntp_origin = (((uint64_t) ntp.origin.sec) << 32) + (uint64_t) ntp.origin.frac;
  uint64_t ntp_xmit = (((uint64_t) ntp.xmit.sec) << 32) + (uint64_t) ntp.xmit.frac;
  uint64_t ntp_dest = (((uint64_t) dest.sec) << 32) + (uint64_t) dest.frac;

  // Compensation as per RFC2030
  int64_t delta = (int64_t) (ntp_recv - ntp_origin) / 2 + (int64_t) (ntp_xmit - ntp_dest) / 2;

  record_result(same_as_last, addr, delta, ntp.stratum, ntp.LI, ((int64_t)(ntp_dest - ntp_origin - (ntp_xmit - ntp_recv))) >> 16, root_maxerr, ntohl(ntp.root_dispersion), ntohl(ntp.root_delay));

#else
  uint64_t ntp_xmit = (((uint64_t) ntp.xmit.sec - NTP_TO_UNIX_EPOCH) << 32) + (uint64_t) ntp.xmit.frac;
  record_result(same_as_last, addr, ntp_xmit, ntp.stratum, ntp.LI, (((int64_t) (system_get_time() - ntp.origin.frac)) << 16) / MICROSECONDS, root_maxerr, ntohl(ntp.root_dispersion), ntohl(ntp.root_delay));
#endif

  sntp_dosend();
}