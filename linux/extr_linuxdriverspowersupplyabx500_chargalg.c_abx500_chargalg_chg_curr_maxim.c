#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int original_iset; int wait_cnt; scalar_t__ max_current; scalar_t__ current_iset; int test_delta_i; scalar_t__ condition_cnt; scalar_t__ level; } ;
struct TYPE_7__ {int inst_curr; } ;
struct TYPE_6__ {scalar_t__ vbus_collapsed; } ;
struct abx500_chargalg {TYPE_5__* bm; TYPE_3__ ccm; int /*<<< orphan*/  dev; TYPE_2__ batt_data; TYPE_1__ events; } ;
typedef  enum maxim_ret { ____Placeholder_maxim_ret } maxim_ret ;
struct TYPE_10__ {TYPE_4__* maxi; } ;
struct TYPE_9__ {scalar_t__ wait_cycles; int /*<<< orphan*/  ena_maxi; } ;

/* Variables and functions */
 int MAXIM_RET_CHANGE ; 
 int MAXIM_RET_IBAT_TOO_HIGH ; 
 int MAXIM_RET_NOACTION ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static enum maxim_ret abx500_chargalg_chg_curr_maxim(struct abx500_chargalg *di)
{
	int delta_i;

	if (!di->bm->maxi->ena_maxi)
		return MAXIM_RET_NOACTION;

	delta_i = di->ccm.original_iset - di->batt_data.inst_curr;

	if (di->events.vbus_collapsed) {
		dev_dbg(di->dev, "Charger voltage has collapsed %d\n",
				di->ccm.wait_cnt);
		if (di->ccm.wait_cnt == 0) {
			dev_dbg(di->dev, "lowering current\n");
			di->ccm.wait_cnt++;
			di->ccm.condition_cnt = di->bm->maxi->wait_cycles;
			di->ccm.max_current =
				di->ccm.current_iset - di->ccm.test_delta_i;
			di->ccm.current_iset = di->ccm.max_current;
			di->ccm.level--;
			return MAXIM_RET_CHANGE;
		} else {
			dev_dbg(di->dev, "waiting\n");
			/* Let's go in here twice before lowering curr again */
			di->ccm.wait_cnt = (di->ccm.wait_cnt + 1) % 3;
			return MAXIM_RET_NOACTION;
		}
	}

	di->ccm.wait_cnt = 0;

	if ((di->batt_data.inst_curr > di->ccm.original_iset)) {
		dev_dbg(di->dev, " Maximization Ibat (%dmA) too high"
			" (limit %dmA) (current iset: %dmA)!\n",
			di->batt_data.inst_curr, di->ccm.original_iset,
			di->ccm.current_iset);

		if (di->ccm.current_iset == di->ccm.original_iset)
			return MAXIM_RET_NOACTION;

		di->ccm.condition_cnt = di->bm->maxi->wait_cycles;
		di->ccm.current_iset = di->ccm.original_iset;
		di->ccm.level = 0;

		return MAXIM_RET_IBAT_TOO_HIGH;
	}

	if (delta_i > di->ccm.test_delta_i &&
		(di->ccm.current_iset + di->ccm.test_delta_i) <
		di->ccm.max_current) {
		if (di->ccm.condition_cnt-- == 0) {
			/* Increse the iset with cco.test_delta_i */
			di->ccm.condition_cnt = di->bm->maxi->wait_cycles;
			di->ccm.current_iset += di->ccm.test_delta_i;
			di->ccm.level++;
			dev_dbg(di->dev, " Maximization needed, increase"
				" with %d mA to %dmA (Optimal ibat: %d)"
				" Level %d\n",
				di->ccm.test_delta_i,
				di->ccm.current_iset,
				di->ccm.original_iset,
				di->ccm.level);
			return MAXIM_RET_CHANGE;
		} else {
			return MAXIM_RET_NOACTION;
		}
	}  else {
		di->ccm.condition_cnt = di->bm->maxi->wait_cycles;
		return MAXIM_RET_NOACTION;
	}
}