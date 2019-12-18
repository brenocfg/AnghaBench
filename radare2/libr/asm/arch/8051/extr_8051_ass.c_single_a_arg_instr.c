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

/* Variables and functions */
 scalar_t__ r_str_casecmp (char*,char const*) ; 
 int single_byte_instr (int /*<<< orphan*/  const,int /*<<< orphan*/ **) ; 

__attribute__((used)) static bool single_a_arg_instr(ut8 const firstbyte, char const*arg
	, ut8 **out)
{
	if (r_str_casecmp ("a", arg)) {
		return false;
	}
	return single_byte_instr (firstbyte, out);
}