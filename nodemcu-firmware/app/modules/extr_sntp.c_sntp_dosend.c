#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long uint32_t ;
struct rtc_timeval {scalar_t__ tv_sec; int /*<<< orphan*/  tv_usec; } ;
struct pbuf {int /*<<< orphan*/  payload; } ;
typedef  int /*<<< orphan*/  req ;
struct TYPE_9__ {void* frac; void* sec; } ;
struct TYPE_10__ {int ver; int mode; TYPE_1__ xmit; } ;
typedef  TYPE_2__ ntp_frame_t ;
struct TYPE_12__ {size_t server_pos; int kodbits; int attempts; int /*<<< orphan*/  timer; int /*<<< orphan*/  pcb; TYPE_1__ cookie; } ;
struct TYPE_11__ {scalar_t__ addr; } ;

/* Variables and functions */
 int MAX_ATTEMPTS ; 
 int /*<<< orphan*/  NTP_MEM_ERR ; 
 int /*<<< orphan*/  NTP_PORT ; 
 int /*<<< orphan*/  PBUF_RAM ; 
 int /*<<< orphan*/  PBUF_TRANSPORT ; 
 int /*<<< orphan*/  SNTP_HANDLE_RESULT_ID ; 
 int /*<<< orphan*/  SWTIMER_REG_CB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SWTIMER_RESUME ; 
 unsigned long const US_TO_FRAC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_zero_base_timeofday (struct rtc_timeval*) ; 
 void* htonl (unsigned long const) ; 
 int /*<<< orphan*/  ipaddr_ntoa (TYPE_3__*) ; 
 int /*<<< orphan*/  on_timeout ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  os_memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_timer_arm (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_timer_disarm (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_timer_setfn (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct pbuf* pbuf_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pbuf_free (struct pbuf*) ; 
 int /*<<< orphan*/  rtctime_gettimeofday (struct rtc_timeval*) ; 
 int server_count ; 
 TYPE_3__* serverp ; 
 int /*<<< orphan*/  sntp_dbg (char*,int,...) ; 
 TYPE_4__* state ; 
 unsigned long const system_get_time () ; 
 int /*<<< orphan*/  task_post_high (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_post_low (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasknumber ; 
 unsigned long const the_offset ; 
 int udp_sendto (int /*<<< orphan*/ ,struct pbuf*,TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sntp_dosend ()
{
  do {
    if (state->server_pos < 0) {
      os_timer_disarm(&state->timer);
      os_timer_setfn(&state->timer, on_timeout, NULL);
      SWTIMER_REG_CB(on_timeout, SWTIMER_RESUME);
        //The function on_timeout calls this function(sntp_dosend) again to handle time sync timeout.
        //My guess: Since the WiFi connection is restored after waking from light sleep, it would be possible to contact the SNTP server, So why not let it
      state->server_pos = 0;
    } else {
      ++state->server_pos;
    }

    if (state->server_pos >= server_count) {
      state->server_pos = 0;
      ++state->attempts;
    }

    if (state->attempts >= MAX_ATTEMPTS || state->attempts * server_count >= 8) {
      task_post_high(tasknumber, SNTP_HANDLE_RESULT_ID);
      return;
    }
  } while (serverp[state->server_pos].addr == 0 || (state->kodbits & (1 << state->server_pos)));

  sntp_dbg("sntp: server %s (%d), attempt %d\n", ipaddr_ntoa(serverp + state->server_pos), state->server_pos, state->attempts);

  struct pbuf *p = pbuf_alloc (PBUF_TRANSPORT, sizeof (ntp_frame_t), PBUF_RAM);
  if (!p) {
    task_post_low(tasknumber, NTP_MEM_ERR);
    return;
  }

  ntp_frame_t req;
  os_memset (&req, 0, sizeof (req));
  req.ver = 4;
  req.mode = 3; // client
#ifdef LUA_USE_MODULES_RTCTIME
  const uint32_t NTP_TO_UNIX_EPOCH = 2208988800ul;
  struct rtc_timeval tv;
  rtctime_gettimeofday (&tv);
  if (tv.tv_sec == 0) {
    get_zero_base_timeofday(&tv);
  }
  req.xmit.sec = htonl (tv.tv_sec - the_offset + NTP_TO_UNIX_EPOCH);
  req.xmit.frac = htonl (US_TO_FRAC(tv.tv_usec));
#else
  req.xmit.frac = htonl (system_get_time ());
#endif
  state->cookie = req.xmit;

  os_memcpy (p->payload, &req, sizeof (req));
  int ret = udp_sendto (state->pcb, p, serverp + state->server_pos, NTP_PORT);
  sntp_dbg("sntp: send: %d\n", ret);
  pbuf_free (p);

  // Ignore send errors -- let the timeout handle it

  os_timer_arm (&state->timer, 1000, 0);
}