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
typedef  int /*<<< orphan*/  tkr_dummy ;
struct tk_read_base {int /*<<< orphan*/ * clock; scalar_t__ base; scalar_t__ base_real; } ;
struct timekeeper {struct tk_read_base tkr_raw; scalar_t__ offs_real; struct tk_read_base tkr_mono; } ;

/* Variables and functions */
 int /*<<< orphan*/  cycles_at_suspend ; 
 int /*<<< orphan*/  dummy_clock ; 
 int /*<<< orphan*/  memcpy (struct tk_read_base*,struct tk_read_base const*,int) ; 
 int /*<<< orphan*/  tk_clock_read (struct tk_read_base const*) ; 
 int /*<<< orphan*/  tk_fast_mono ; 
 int /*<<< orphan*/  tk_fast_raw ; 
 int /*<<< orphan*/  update_fast_timekeeper (struct tk_read_base*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void halt_fast_timekeeper(const struct timekeeper *tk)
{
	static struct tk_read_base tkr_dummy;
	const struct tk_read_base *tkr = &tk->tkr_mono;

	memcpy(&tkr_dummy, tkr, sizeof(tkr_dummy));
	cycles_at_suspend = tk_clock_read(tkr);
	tkr_dummy.clock = &dummy_clock;
	tkr_dummy.base_real = tkr->base + tk->offs_real;
	update_fast_timekeeper(&tkr_dummy, &tk_fast_mono);

	tkr = &tk->tkr_raw;
	memcpy(&tkr_dummy, tkr, sizeof(tkr_dummy));
	tkr_dummy.clock = &dummy_clock;
	update_fast_timekeeper(&tkr_dummy, &tk_fast_raw);
}