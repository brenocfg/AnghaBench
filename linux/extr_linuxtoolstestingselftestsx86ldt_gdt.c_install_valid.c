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
typedef  int /*<<< orphan*/  uint32_t ;
struct user_desc {int contents; int /*<<< orphan*/  seg_not_present; scalar_t__ seg_32bit; } ;

/* Variables and functions */
 int install_valid_mode (struct user_desc const*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static bool install_valid(const struct user_desc *desc, uint32_t ar)
{
	bool ret = install_valid_mode(desc, ar, false, true);

	if (desc->contents <= 1 && desc->seg_32bit &&
	    !desc->seg_not_present) {
		/* Should work in the GDT, too. */
		install_valid_mode(desc, ar, false, false);
	}

	return ret;
}