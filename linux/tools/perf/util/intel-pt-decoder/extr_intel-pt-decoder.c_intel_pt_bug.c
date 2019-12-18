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
struct intel_pt_decoder {int /*<<< orphan*/  pkt_state; } ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  INTEL_PT_STATE_NO_PSB ; 
 int /*<<< orphan*/  intel_pt_log (char*) ; 

__attribute__((used)) static int intel_pt_bug(struct intel_pt_decoder *decoder)
{
	intel_pt_log("ERROR: Internal error\n");
	decoder->pkt_state = INTEL_PT_STATE_NO_PSB;
	return -ENOSYS;
}