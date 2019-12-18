#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct instruction {TYPE_1__* call_dest; } ;
struct TYPE_2__ {char const* name; } ;

/* Variables and functions */

__attribute__((used)) static inline const char *call_dest_name(struct instruction *insn)
{
	if (insn->call_dest)
		return insn->call_dest->name;

	return "{dynamic}";
}