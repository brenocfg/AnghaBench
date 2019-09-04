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
struct nau8825 {scalar_t__ xtalk_state; int xtalk_protect; int /*<<< orphan*/  xtalk_work; scalar_t__ xtalk_enable; } ;

/* Variables and functions */
 scalar_t__ NAU8825_XTALK_DONE ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nau8825_sema_reset (struct nau8825*) ; 
 int /*<<< orphan*/  nau8825_xtalk_clean (struct nau8825*,int) ; 

__attribute__((used)) static void nau8825_xtalk_cancel(struct nau8825 *nau8825)
{
	/* If the crosstalk is eanbled and the process is on going,
	 * the driver forces to cancel the crosstalk task and
	 * restores the configuration to original status.
	 */
	if (nau8825->xtalk_enable && nau8825->xtalk_state !=
		NAU8825_XTALK_DONE) {
		cancel_work_sync(&nau8825->xtalk_work);
		nau8825_xtalk_clean(nau8825, true);
	}
	/* Reset parameters for cross talk suppression function */
	nau8825_sema_reset(nau8825);
	nau8825->xtalk_state = NAU8825_XTALK_DONE;
	nau8825->xtalk_protect = false;
}