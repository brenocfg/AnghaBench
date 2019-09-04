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
struct rfbi_timings {scalar_t__* tim; int /*<<< orphan*/  converted; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DSSERR (char*) ; 
 int /*<<< orphan*/  REG_FLD_MOD (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  RFBI_CONFIG (int) ; 
 int /*<<< orphan*/  RFBI_CYCLE_TIME (int) ; 
 int /*<<< orphan*/  RFBI_ONOFF_TIME (int) ; 
 int calc_extif_timings (struct rfbi_timings*) ; 
 int /*<<< orphan*/  rfbi_print_timings () ; 
 int /*<<< orphan*/  rfbi_write_reg (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void rfbi_set_timings(int rfbi_module, struct rfbi_timings *t)
{
	int r;

	if (!t->converted) {
		r = calc_extif_timings(t);
		if (r < 0)
			DSSERR("Failed to calc timings\n");
	}

	BUG_ON(!t->converted);

	rfbi_write_reg(RFBI_ONOFF_TIME(rfbi_module), t->tim[0]);
	rfbi_write_reg(RFBI_CYCLE_TIME(rfbi_module), t->tim[1]);

	/* TIMEGRANULARITY */
	REG_FLD_MOD(RFBI_CONFIG(rfbi_module),
		    (t->tim[2] ? 1 : 0), 4, 4);

	rfbi_print_timings();
}