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
struct ubifs_info {int assert_action; } ;

/* Variables and functions */
#define  ASSACT_PANIC 130 
#define  ASSACT_REPORT 129 
#define  ASSACT_RO 128 
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  ubifs_err (struct ubifs_info*,char*,char const*,char const*,int) ; 
 int /*<<< orphan*/  ubifs_ro_mode (struct ubifs_info*,int /*<<< orphan*/ ) ; 

void ubifs_assert_failed(struct ubifs_info *c, const char *expr,
			 const char *file, int line)
{
	ubifs_err(c, "UBIFS assert failed: %s, in %s:%u", expr, file, line);

	switch (c->assert_action) {
		case ASSACT_PANIC:
		BUG();
		break;

		case ASSACT_RO:
		ubifs_ro_mode(c, -EINVAL);
		break;

		case ASSACT_REPORT:
		default:
		dump_stack();
		break;

	}
}