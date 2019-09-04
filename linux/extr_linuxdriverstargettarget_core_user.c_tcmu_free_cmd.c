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
struct tcmu_cmd {int /*<<< orphan*/  dbi; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct tcmu_cmd*) ; 
 int /*<<< orphan*/  tcmu_cmd_cache ; 

__attribute__((used)) static inline void tcmu_free_cmd(struct tcmu_cmd *tcmu_cmd)
{
	kfree(tcmu_cmd->dbi);
	kmem_cache_free(tcmu_cmd_cache, tcmu_cmd);
}