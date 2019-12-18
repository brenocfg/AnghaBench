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
typedef  int u8 ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int addrtype_validate_match_data(struct nlattr **tb, u8 mrev)
{
	if (mrev != 1) {
		pr_err("only addrtype match revision 1 supported");
		return -EINVAL;
	}

	return 0;
}