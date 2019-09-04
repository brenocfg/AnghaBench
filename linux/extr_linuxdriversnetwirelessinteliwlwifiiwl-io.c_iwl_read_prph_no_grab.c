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
struct iwl_trans {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  iwl_trans_read_prph (struct iwl_trans*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_iwlwifi_dev_ioread_prph32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u32 iwl_read_prph_no_grab(struct iwl_trans *trans, u32 ofs)
{
	u32 val = iwl_trans_read_prph(trans, ofs);
	trace_iwlwifi_dev_ioread_prph32(trans->dev, ofs, val);
	return val;
}