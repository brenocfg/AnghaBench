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
struct intel_pt_decoder {int have_last_ip; int /*<<< orphan*/  last_ip; int /*<<< orphan*/  packet; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_pt_calc_ip (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void intel_pt_set_last_ip(struct intel_pt_decoder *decoder)
{
	decoder->last_ip = intel_pt_calc_ip(&decoder->packet, decoder->last_ip);
	decoder->have_last_ip = true;
}