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
struct src_mgr_ctrl_blk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct src_mgr_ctrl_blk*) ; 

__attribute__((used)) static int src_mgr_put_ctrl_blk(void *blk)
{
	kfree((struct src_mgr_ctrl_blk *)blk);

	return 0;
}