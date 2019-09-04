#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct qla_hw_data {int /*<<< orphan*/  loop_id_map; } ;
struct TYPE_4__ {scalar_t__ loop_id; TYPE_2__* vha; } ;
typedef  TYPE_1__ fc_port_t ;
struct TYPE_5__ {struct qla_hw_data* hw; } ;

/* Variables and functions */
 scalar_t__ FC_NO_LOOP_ID ; 
 int /*<<< orphan*/  clear_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ qla2x00_is_reserved_id (TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static inline void
qla2x00_clear_loop_id(fc_port_t *fcport) {
	struct qla_hw_data *ha = fcport->vha->hw;

	if (fcport->loop_id == FC_NO_LOOP_ID ||
	    qla2x00_is_reserved_id(fcport->vha, fcport->loop_id))
		return;

	clear_bit(fcport->loop_id, ha->loop_id_map);
	fcport->loop_id = FC_NO_LOOP_ID;
}