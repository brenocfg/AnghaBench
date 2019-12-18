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
struct TYPE_3__ {scalar_t__ base; scalar_t__ base_real; } ;
struct timekeeper {int /*<<< orphan*/  clock_was_set_seq; TYPE_1__ tkr_raw; TYPE_1__ tkr_mono; scalar_t__ offs_real; scalar_t__ ntp_error; } ;
struct TYPE_4__ {int /*<<< orphan*/  timekeeper; } ;

/* Variables and functions */
 unsigned int TK_CLEAR_NTP ; 
 unsigned int TK_CLOCK_WAS_SET ; 
 unsigned int TK_MIRROR ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ntp_clear () ; 
 int /*<<< orphan*/  shadow_timekeeper ; 
 TYPE_2__ tk_core ; 
 int /*<<< orphan*/  tk_fast_mono ; 
 int /*<<< orphan*/  tk_fast_raw ; 
 int /*<<< orphan*/  tk_update_ktime_data (struct timekeeper*) ; 
 int /*<<< orphan*/  tk_update_leap_state (struct timekeeper*) ; 
 int /*<<< orphan*/  update_fast_timekeeper (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_pvclock_gtod (struct timekeeper*,unsigned int) ; 
 int /*<<< orphan*/  update_vsyscall (struct timekeeper*) ; 

__attribute__((used)) static void timekeeping_update(struct timekeeper *tk, unsigned int action)
{
	if (action & TK_CLEAR_NTP) {
		tk->ntp_error = 0;
		ntp_clear();
	}

	tk_update_leap_state(tk);
	tk_update_ktime_data(tk);

	update_vsyscall(tk);
	update_pvclock_gtod(tk, action & TK_CLOCK_WAS_SET);

	tk->tkr_mono.base_real = tk->tkr_mono.base + tk->offs_real;
	update_fast_timekeeper(&tk->tkr_mono, &tk_fast_mono);
	update_fast_timekeeper(&tk->tkr_raw,  &tk_fast_raw);

	if (action & TK_CLOCK_WAS_SET)
		tk->clock_was_set_seq++;
	/*
	 * The mirroring of the data to the shadow-timekeeper needs
	 * to happen last here to ensure we don't over-write the
	 * timekeeper structure on the next update with stale data
	 */
	if (action & TK_MIRROR)
		memcpy(&shadow_timekeeper, &tk_core.timekeeper,
		       sizeof(tk_core.timekeeper));
}