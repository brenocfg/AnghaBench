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
struct tool_ctx {int /*<<< orphan*/  msg_wq; int /*<<< orphan*/  db_wq; int /*<<< orphan*/  link_wq; struct ntb_dev* ntb; } ;
struct ntb_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct tool_ctx* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct tool_ctx* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 scalar_t__ ntb_db_is_unsafe (struct ntb_dev*) ; 
 scalar_t__ ntb_spad_is_unsafe (struct ntb_dev*) ; 

__attribute__((used)) static struct tool_ctx *tool_create_data(struct ntb_dev *ntb)
{
	struct tool_ctx *tc;

	tc = devm_kzalloc(&ntb->dev, sizeof(*tc), GFP_KERNEL);
	if (tc == NULL)
		return ERR_PTR(-ENOMEM);

	tc->ntb = ntb;
	init_waitqueue_head(&tc->link_wq);
	init_waitqueue_head(&tc->db_wq);
	init_waitqueue_head(&tc->msg_wq);

	if (ntb_db_is_unsafe(ntb))
		dev_dbg(&ntb->dev, "doorbell is unsafe\n");

	if (ntb_spad_is_unsafe(ntb))
		dev_dbg(&ntb->dev, "scratchpad is unsafe\n");

	return tc;
}