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
struct src_rsc_ctrl_blk {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct src_rsc_ctrl_blk* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int src_get_rsc_ctrl_blk(void **rblk)
{
	struct src_rsc_ctrl_blk *blk;

	*rblk = NULL;
	blk = kzalloc(sizeof(*blk), GFP_KERNEL);
	if (!blk)
		return -ENOMEM;

	*rblk = blk;

	return 0;
}