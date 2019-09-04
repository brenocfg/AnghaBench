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
typedef  int /*<<< orphan*/  uint16_t ;
struct dwc_otg_hcd_pipe_info {int /*<<< orphan*/  mps; } ;

/* Variables and functions */

__attribute__((used)) static inline uint16_t dwc_otg_hcd_get_mps(struct dwc_otg_hcd_pipe_info *pipe)
{
	return pipe->mps;
}