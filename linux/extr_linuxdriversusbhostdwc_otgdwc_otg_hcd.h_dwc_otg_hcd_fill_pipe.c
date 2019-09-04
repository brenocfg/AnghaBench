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
typedef  void* uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct dwc_otg_hcd_pipe_info {int /*<<< orphan*/  mps; void* pipe_dir; void* pipe_type; void* ep_num; void* dev_addr; } ;

/* Variables and functions */

__attribute__((used)) static inline void dwc_otg_hcd_fill_pipe(struct dwc_otg_hcd_pipe_info *pipe,
					 uint8_t devaddr, uint8_t ep_num,
					 uint8_t pipe_type, uint8_t pipe_dir,
					 uint16_t mps)
{
	pipe->dev_addr = devaddr;
	pipe->ep_num = ep_num;
	pipe->pipe_type = pipe_type;
	pipe->pipe_dir = pipe_dir;
	pipe->mps = mps;
}