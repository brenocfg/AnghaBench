#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  ip_addr_t ;
typedef  int int64_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_3__ {int stratum; int delay; int server_pos; int delay_frac; int root_maxerr; int root_dispersion; int root_delay; int delta; int LI; int /*<<< orphan*/  when; int /*<<< orphan*/  server; } ;
struct TYPE_4__ {int last_server_pos; TYPE_1__ best; } ;

/* Variables and functions */
 scalar_t__ FRAC16_TO_US (int) ; 
 int /*<<< orphan*/  ipaddr_ntoa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sntp_dbg (char*,...) ; 
 TYPE_2__* state ; 
 int /*<<< orphan*/  system_get_time () ; 

__attribute__((used)) static void record_result(int server_pos, ip_addr_t *addr, int64_t delta, int stratum, int LI, uint32_t delay_frac, uint32_t root_maxerr, uint32_t root_dispersion, uint32_t root_delay) {
  sntp_dbg("Recording %s: delta=%08x.%08x, stratum=%d, li=%d, delay=%dus, root_maxerr=%dus",
      ipaddr_ntoa(addr), (uint32_t) (delta >> 32), (uint32_t) (delta & 0xffffffff), stratum, LI, (int32_t) FRAC16_TO_US(delay_frac), (int32_t) FRAC16_TO_US(root_maxerr));
  // I want to favor close by servers as they probably have a more consistent clock,
  int delay = root_delay * 2 + delay_frac;
  if (state->last_server_pos == server_pos) {
    delay -= delay >> 2;               // 25% bonus to last best server
  }

  if (!state->best.stratum || delay < state->best.delay) {
    sntp_dbg("   --BEST\n");
    state->best.server = *addr;
    state->best.server_pos = server_pos;
    state->best.delay = delay;
    state->best.delay_frac = delay_frac;
    state->best.root_maxerr = root_maxerr;
    state->best.root_dispersion = root_dispersion;
    state->best.root_delay = root_delay;
    state->best.delta = delta;
    state->best.stratum = stratum;
    state->best.LI = LI;
    state->best.when = system_get_time();
  } else {
    sntp_dbg("\n");
  }
}