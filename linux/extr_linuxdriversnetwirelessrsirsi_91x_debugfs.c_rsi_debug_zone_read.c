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
struct seq_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSM_ZONE ; 
 int /*<<< orphan*/  rsi_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsi_zone_enabled ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rsi_debug_zone_read(struct seq_file *seq, void *data)
{
	rsi_dbg(FSM_ZONE, "%x: rsi_enabled zone", rsi_zone_enabled);
	seq_printf(seq, "The zones available are %#x\n",
		   rsi_zone_enabled);
	return 0;
}