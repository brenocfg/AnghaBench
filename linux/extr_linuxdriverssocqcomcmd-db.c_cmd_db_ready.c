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

/* Variables and functions */
 int EINVAL ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/ * cmd_db_header ; 
 int /*<<< orphan*/  cmd_db_magic_matches (int /*<<< orphan*/ *) ; 

int cmd_db_ready(void)
{
	if (cmd_db_header == NULL)
		return -EPROBE_DEFER;
	else if (!cmd_db_magic_matches(cmd_db_header))
		return -EINVAL;

	return 0;
}