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
struct pvscsi_adapter {int /*<<< orphan*/  use_req_threshold; struct PVSCSIRingsState* rings_state; } ;
struct PVSCSIRingsState {scalar_t__ reqProdIdx; scalar_t__ reqConsIdx; scalar_t__ reqCallThreshold; } ;

/* Variables and functions */
 int /*<<< orphan*/  pvscsi_kick_rw_io (struct pvscsi_adapter const*) ; 
 int /*<<< orphan*/  pvscsi_process_request_ring (struct pvscsi_adapter const*) ; 
 scalar_t__ scsi_is_rw (unsigned char) ; 

__attribute__((used)) static void pvscsi_kick_io(const struct pvscsi_adapter *adapter,
			   unsigned char op)
{
	if (scsi_is_rw(op)) {
		struct PVSCSIRingsState *s = adapter->rings_state;

		if (!adapter->use_req_threshold ||
		    s->reqProdIdx - s->reqConsIdx >= s->reqCallThreshold)
			pvscsi_kick_rw_io(adapter);
	} else {
		pvscsi_process_request_ring(adapter);
	}
}