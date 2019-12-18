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
struct intel_pt_decoder {int have_tma; scalar_t__ timestamp; int /*<<< orphan*/  pkt_state; scalar_t__ ip; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTEL_PT_STATE_NO_PSB ; 

__attribute__((used)) static void intel_pt_reposition(struct intel_pt_decoder *decoder)
{
	decoder->ip = 0;
	decoder->pkt_state = INTEL_PT_STATE_NO_PSB;
	decoder->timestamp = 0;
	decoder->have_tma = false;
}