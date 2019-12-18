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
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ut16 ;

/* Variables and functions */
 int single_a_arg_instr (int,char const* const,int /*<<< orphan*/ **) ; 

__attribute__((used)) static bool mnem_da(char const*const*arg, ut16 pc, ut8**out) {
	return single_a_arg_instr (0xd4, arg[0], out);
}