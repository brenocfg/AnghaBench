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
typedef  int uint8_t ;
struct dwc_otg_hcd_pipe_info {scalar_t__ pipe_type; } ;

/* Variables and functions */
 scalar_t__ UE_INTERRUPT ; 

__attribute__((used)) static inline uint8_t dwc_otg_hcd_is_pipe_int(struct dwc_otg_hcd_pipe_info
					      *pipe)
{
	return (pipe->pipe_type == UE_INTERRUPT);
}