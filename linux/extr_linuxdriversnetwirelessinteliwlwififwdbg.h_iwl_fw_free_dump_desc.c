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
struct TYPE_2__ {int /*<<< orphan*/ * trig; int /*<<< orphan*/ * desc; } ;
struct iwl_fw_runtime {TYPE_1__ dump; } ;

/* Variables and functions */
 int /*<<< orphan*/  iwl_dump_desc_assert ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void iwl_fw_free_dump_desc(struct iwl_fw_runtime *fwrt)
{
	if (fwrt->dump.desc != &iwl_dump_desc_assert)
		kfree(fwrt->dump.desc);
	fwrt->dump.desc = NULL;
	fwrt->dump.trig = NULL;
}