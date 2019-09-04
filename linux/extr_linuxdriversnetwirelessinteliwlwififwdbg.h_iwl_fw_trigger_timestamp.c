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
typedef  int /*<<< orphan*/  u32 ;
struct iwl_fw_runtime {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void iwl_fw_trigger_timestamp(struct iwl_fw_runtime *fwrt,
					    u32 delay) {}