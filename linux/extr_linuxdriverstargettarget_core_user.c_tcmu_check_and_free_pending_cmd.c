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
struct tcmu_cmd {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TCMU_CMD_BIT_EXPIRED ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct tcmu_cmd*) ; 
 int /*<<< orphan*/  tcmu_cmd_cache ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tcmu_check_and_free_pending_cmd(struct tcmu_cmd *cmd)
{
	if (test_bit(TCMU_CMD_BIT_EXPIRED, &cmd->flags)) {
		kmem_cache_free(tcmu_cmd_cache, cmd);
		return 0;
	}
	return -EINVAL;
}