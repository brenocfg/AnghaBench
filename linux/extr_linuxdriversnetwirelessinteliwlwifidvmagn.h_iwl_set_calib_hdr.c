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
typedef  int /*<<< orphan*/  u8 ;
struct iwl_calib_hdr {int groups_num; int data_valid; scalar_t__ first_group; int /*<<< orphan*/  op_code; } ;

/* Variables and functions */

__attribute__((used)) static inline void iwl_set_calib_hdr(struct iwl_calib_hdr *hdr, u8 cmd)
{
	hdr->op_code = cmd;
	hdr->first_group = 0;
	hdr->groups_num = 1;
	hdr->data_valid = 1;
}