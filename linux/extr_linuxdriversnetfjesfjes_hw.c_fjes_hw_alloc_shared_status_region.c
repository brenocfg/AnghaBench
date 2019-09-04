#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {TYPE_2__* share; } ;
struct fjes_hw {int max_epid; TYPE_1__ hw_info; } ;
struct fjes_device_shared_info {int dummy; } ;
struct TYPE_4__ {int epnum; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_2__* kzalloc (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fjes_hw_alloc_shared_status_region(struct fjes_hw *hw)
{
	size_t size;

	size = sizeof(struct fjes_device_shared_info) +
	    (sizeof(u8) * hw->max_epid);
	hw->hw_info.share = kzalloc(size, GFP_KERNEL);
	if (!hw->hw_info.share)
		return -ENOMEM;

	hw->hw_info.share->epnum = hw->max_epid;

	return 0;
}