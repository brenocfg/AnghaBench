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
struct comedi_cmd {unsigned int chanlist_len; unsigned int convert_arg; unsigned int scan_begin_arg; } ;

/* Variables and functions */
 unsigned int UINT_MAX ; 

__attribute__((used)) static int pci230_ai_check_scan_period(struct comedi_cmd *cmd)
{
	unsigned int min_scan_period, chanlist_len;
	int err = 0;

	chanlist_len = cmd->chanlist_len;
	if (cmd->chanlist_len == 0)
		chanlist_len = 1;

	min_scan_period = chanlist_len * cmd->convert_arg;
	if (min_scan_period < chanlist_len ||
	    min_scan_period < cmd->convert_arg) {
		/* Arithmetic overflow. */
		min_scan_period = UINT_MAX;
		err++;
	}
	if (cmd->scan_begin_arg < min_scan_period) {
		cmd->scan_begin_arg = min_scan_period;
		err++;
	}

	return !err;
}