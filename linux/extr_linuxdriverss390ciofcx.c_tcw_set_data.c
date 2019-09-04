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
typedef  void* u64 ;
struct tcw {int /*<<< orphan*/  flags; void* output; scalar_t__ w; void* input; scalar_t__ r; } ;
typedef  scalar_t__ addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  TCW_FLAGS_INPUT_TIDA ; 
 int /*<<< orphan*/  TCW_FLAGS_OUTPUT_TIDA ; 

void tcw_set_data(struct tcw *tcw, void *data, int use_tidal)
{
	if (tcw->r) {
		tcw->input = (u64) ((addr_t) data);
		if (use_tidal)
			tcw->flags |= TCW_FLAGS_INPUT_TIDA;
	} else if (tcw->w) {
		tcw->output = (u64) ((addr_t) data);
		if (use_tidal)
			tcw->flags |= TCW_FLAGS_OUTPUT_TIDA;
	}
}