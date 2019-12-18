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
struct pt_regs {int dummy; } ;
typedef  int kdb_reason_t ;
typedef  int /*<<< orphan*/  kdb_dbtrap_t ;

/* Variables and functions */
 int /*<<< orphan*/  DOING_KGDB ; 
 int /*<<< orphan*/  DOING_SS ; 
 int /*<<< orphan*/  HOLD_CPU ; 
 int /*<<< orphan*/  KDB ; 
 int KDB_CMD_CPU ; 
 int KDB_CMD_GO ; 
 int KDB_CMD_KGDB ; 
 int KDB_CMD_SS ; 
 int /*<<< orphan*/  KDB_DEBUG_STATE (char*,int) ; 
 scalar_t__ KDB_STATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KDB_STATE_CLEAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KDB_STATE_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LEAVING ; 
 int /*<<< orphan*/  SSBPT ; 
 int /*<<< orphan*/  SUPPRESS ; 
 int /*<<< orphan*/  kdb_kbd_cleanup_state () ; 
 int kdb_local (int,int,struct pt_regs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kdb_printf (char*,...) ; 

int kdb_main_loop(kdb_reason_t reason, kdb_reason_t reason2, int error,
	      kdb_dbtrap_t db_result, struct pt_regs *regs)
{
	int result = 1;
	/* Stay in kdb() until 'go', 'ss[b]' or an error */
	while (1) {
		/*
		 * All processors except the one that is in control
		 * will spin here.
		 */
		KDB_DEBUG_STATE("kdb_main_loop 1", reason);
		while (KDB_STATE(HOLD_CPU)) {
			/* state KDB is turned off by kdb_cpu to see if the
			 * other cpus are still live, each cpu in this loop
			 * turns it back on.
			 */
			if (!KDB_STATE(KDB))
				KDB_STATE_SET(KDB);
		}

		KDB_STATE_CLEAR(SUPPRESS);
		KDB_DEBUG_STATE("kdb_main_loop 2", reason);
		if (KDB_STATE(LEAVING))
			break;	/* Another cpu said 'go' */
		/* Still using kdb, this processor is in control */
		result = kdb_local(reason2, error, regs, db_result);
		KDB_DEBUG_STATE("kdb_main_loop 3", result);

		if (result == KDB_CMD_CPU)
			break;

		if (result == KDB_CMD_SS) {
			KDB_STATE_SET(DOING_SS);
			break;
		}

		if (result == KDB_CMD_KGDB) {
			if (!KDB_STATE(DOING_KGDB))
				kdb_printf("Entering please attach debugger "
					   "or use $D#44+ or $3#33\n");
			break;
		}
		if (result && result != 1 && result != KDB_CMD_GO)
			kdb_printf("\nUnexpected kdb_local return code %d\n",
				   result);
		KDB_DEBUG_STATE("kdb_main_loop 4", reason);
		break;
	}
	if (KDB_STATE(DOING_SS))
		KDB_STATE_CLEAR(SSBPT);

	/* Clean up any keyboard devices before leaving */
	kdb_kbd_cleanup_state();

	return result;
}