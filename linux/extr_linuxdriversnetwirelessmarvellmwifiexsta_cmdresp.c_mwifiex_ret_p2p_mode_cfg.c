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
struct mwifiex_private {int dummy; } ;
struct host_cmd_ds_p2p_mode_cfg {int /*<<< orphan*/  mode; } ;
struct TYPE_2__ {struct host_cmd_ds_p2p_mode_cfg mode_cfg; } ;
struct host_cmd_ds_command {TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_unaligned_le16 (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int
mwifiex_ret_p2p_mode_cfg(struct mwifiex_private *priv,
			 struct host_cmd_ds_command *resp,
			 void *data_buf)
{
	struct host_cmd_ds_p2p_mode_cfg *mode_cfg = &resp->params.mode_cfg;

	if (data_buf)
		put_unaligned_le16(le16_to_cpu(mode_cfg->mode), data_buf);

	return 0;
}