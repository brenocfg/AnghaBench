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
struct x86_cpu_id {int member_1; int member_2; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
#define  X86_VENDOR_INTEL 128 
 scalar_t__ x86_match_cpu (struct x86_cpu_id const*) ; 

__attribute__((used)) static int is_byt(void)
{
	bool status = false;
	static const struct x86_cpu_id cpu_ids[] = {
		{ X86_VENDOR_INTEL, 6, 55 }, /* Valleyview, Bay Trail */
		{}
	};
	if (x86_match_cpu(cpu_ids))
		status = true;
	return status;
}