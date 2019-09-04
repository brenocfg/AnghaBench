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
struct tool_ctx {int /*<<< orphan*/  msg_wq; int /*<<< orphan*/  db_wq; int /*<<< orphan*/  link_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tool_clear_data(struct tool_ctx *tc)
{
	wake_up(&tc->link_wq);
	wake_up(&tc->db_wq);
	wake_up(&tc->msg_wq);
}