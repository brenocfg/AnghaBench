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
struct comedi_cmd {scalar_t__ scan_begin_src; scalar_t__ convert_src; unsigned int scan_begin_arg; } ;
typedef  enum scan_mode { ____Placeholder_scan_mode } scan_mode ;

/* Variables and functions */
 int MODE_SINGLE_CHAN ; 
 scalar_t__ TRIG_TIMER ; 

__attribute__((used)) static void labpc_set_ai_scan_period(struct comedi_cmd *cmd,
				     enum scan_mode mode, unsigned int ns)
{
	if (cmd->scan_begin_src != TRIG_TIMER)
		return;

	if (mode == MODE_SINGLE_CHAN && cmd->convert_src == TRIG_TIMER)
		return;

	cmd->scan_begin_arg = ns;
}