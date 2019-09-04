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
typedef  int /*<<< orphan*/  UniChar ;

/* Variables and functions */
 int /*<<< orphan*/  cmd_str ; 
 int /*<<< orphan*/  ctrl_str ; 
 int /*<<< orphan*/  const kCommandUnicode ; 
 int /*<<< orphan*/  const kControlUnicode ; 
 int /*<<< orphan*/  const kOptionUnicode ; 
 int /*<<< orphan*/  const kShiftUnicode ; 
 int /*<<< orphan*/  opt_str ; 
 int /*<<< orphan*/  shift_str ; 
 int /*<<< orphan*/  unichar_to_utf8 (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_utf_8_strings(void)
{
	const UniChar ctrl_uni[]  = {kControlUnicode, 0};
	const UniChar opt_uni[]   = {kOptionUnicode, 0};
	const UniChar shift_uni[] = {kShiftUnicode, 0};
	const UniChar cmd_uni[]   = {kCommandUnicode, 0};

	unichar_to_utf8(ctrl_uni, ctrl_str);
	unichar_to_utf8(opt_uni, opt_str);
	unichar_to_utf8(shift_uni, shift_str);
	unichar_to_utf8(cmd_uni, cmd_str);
}