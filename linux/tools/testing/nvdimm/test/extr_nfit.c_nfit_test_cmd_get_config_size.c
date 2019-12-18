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
struct nd_cmd_get_config_size {int /*<<< orphan*/  max_xfer; int /*<<< orphan*/  config_size; scalar_t__ status; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LABEL_SIZE ; 
 int /*<<< orphan*/  SZ_4K ; 

__attribute__((used)) static int nfit_test_cmd_get_config_size(struct nd_cmd_get_config_size *nd_cmd,
		unsigned int buf_len)
{
	if (buf_len < sizeof(*nd_cmd))
		return -EINVAL;

	nd_cmd->status = 0;
	nd_cmd->config_size = LABEL_SIZE;
	nd_cmd->max_xfer = SZ_4K;

	return 0;
}