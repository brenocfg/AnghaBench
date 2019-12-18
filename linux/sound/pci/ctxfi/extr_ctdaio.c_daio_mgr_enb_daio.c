#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hw {int /*<<< orphan*/  (* daio_mgr_enb_dai ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* daio_mgr_enb_dao ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  ctrl_blk; struct hw* hw; } ;
struct daio_mgr {TYPE_1__ mgr; } ;
struct daio {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ DAIO_OUT_MAX ; 
 int /*<<< orphan*/  daio_device_index (scalar_t__,struct hw*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int daio_mgr_enb_daio(struct daio_mgr *mgr, struct daio *daio)
{
	struct hw *hw = mgr->mgr.hw;

	if (DAIO_OUT_MAX >= daio->type) {
		hw->daio_mgr_enb_dao(mgr->mgr.ctrl_blk,
				daio_device_index(daio->type, hw));
	} else {
		hw->daio_mgr_enb_dai(mgr->mgr.ctrl_blk,
				daio_device_index(daio->type, hw));
	}
	return 0;
}