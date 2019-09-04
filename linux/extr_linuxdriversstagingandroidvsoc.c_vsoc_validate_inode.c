#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct TYPE_6__ {TYPE_2__* dev; TYPE_1__* layout; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {scalar_t__ region_count; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 scalar_t__ iminor (struct inode*) ; 
 TYPE_3__ vsoc_dev ; 

inline int vsoc_validate_inode(struct inode *inode)
{
	if (iminor(inode) >= vsoc_dev.layout->region_count) {
		dev_err(&vsoc_dev.dev->dev,
			"describe_region: invalid region %d\n", iminor(inode));
		return -ENODEV;
	}
	return 0;
}