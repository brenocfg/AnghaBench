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
struct iwl_fw_runtime {int cur_fw_img; } ;
typedef  enum iwl_ucode_type { ____Placeholder_iwl_ucode_type } iwl_ucode_type ;

/* Variables and functions */

__attribute__((used)) static inline void iwl_fw_set_current_image(struct iwl_fw_runtime *fwrt,
					    enum iwl_ucode_type cur_fw_img)
{
	fwrt->cur_fw_img = cur_fw_img;
}