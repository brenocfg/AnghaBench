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
struct tool_ctx {int /*<<< orphan*/  ntb; } ;

/* Variables and functions */
 int ntb_set_ctx (int /*<<< orphan*/ ,struct tool_ctx*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tool_ops ; 

__attribute__((used)) static int tool_init_ntb(struct tool_ctx *tc)
{
	return ntb_set_ctx(tc->ntb, tc, &tool_ops);
}