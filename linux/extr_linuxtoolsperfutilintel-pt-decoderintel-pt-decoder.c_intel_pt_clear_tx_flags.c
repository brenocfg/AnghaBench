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
struct intel_pt_decoder {scalar_t__ tx_flags; } ;

/* Variables and functions */

__attribute__((used)) static inline void intel_pt_clear_tx_flags(struct intel_pt_decoder *decoder)
{
	decoder->tx_flags = 0;
}