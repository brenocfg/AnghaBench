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
typedef  int u32 ;
struct comedi_device {int dummy; } ;
struct comedi_cmd {int convert_arg; } ;

/* Variables and functions */
 int TIMER_BASE ; 

__attribute__((used)) static u32 ai_convert_counter_6xxx(const struct comedi_device *dev,
				   const struct comedi_cmd *cmd)
{
	/* supposed to load counter with desired divisor minus 3 */
	return cmd->convert_arg / TIMER_BASE - 3;
}