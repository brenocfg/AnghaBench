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
struct tool_ctx {int dummy; } ;
struct ntb_dev {int dummy; } ;
struct ntb_client {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct tool_ctx*) ; 
 int PTR_ERR (struct tool_ctx*) ; 
 int /*<<< orphan*/  tool_clear_data (struct tool_ctx*) ; 
 int /*<<< orphan*/  tool_clear_mws (struct tool_ctx*) ; 
 struct tool_ctx* tool_create_data (struct ntb_dev*) ; 
 int tool_init_msgs (struct tool_ctx*) ; 
 int tool_init_mws (struct tool_ctx*) ; 
 int tool_init_ntb (struct tool_ctx*) ; 
 int tool_init_peers (struct tool_ctx*) ; 
 int tool_init_spads (struct tool_ctx*) ; 
 int /*<<< orphan*/  tool_setup_dbgfs (struct tool_ctx*) ; 

__attribute__((used)) static int tool_probe(struct ntb_client *self, struct ntb_dev *ntb)
{
	struct tool_ctx *tc;
	int ret;

	tc = tool_create_data(ntb);
	if (IS_ERR(tc))
		return PTR_ERR(tc);

	ret = tool_init_peers(tc);
	if (ret != 0)
		goto err_clear_data;

	ret = tool_init_mws(tc);
	if (ret != 0)
		goto err_clear_data;

	ret = tool_init_spads(tc);
	if (ret != 0)
		goto err_clear_mws;

	ret = tool_init_msgs(tc);
	if (ret != 0)
		goto err_clear_mws;

	ret = tool_init_ntb(tc);
	if (ret != 0)
		goto err_clear_mws;

	tool_setup_dbgfs(tc);

	return 0;

err_clear_mws:
	tool_clear_mws(tc);

err_clear_data:
	tool_clear_data(tc);

	return ret;
}