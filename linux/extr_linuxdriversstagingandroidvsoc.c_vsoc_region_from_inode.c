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
struct vsoc_device_region {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {struct vsoc_device_region* regions; } ;

/* Variables and functions */
 size_t iminor (struct inode*) ; 
 TYPE_1__ vsoc_dev ; 

__attribute__((used)) static
inline struct vsoc_device_region *vsoc_region_from_inode(struct inode *inode)
{
	return &vsoc_dev.regions[iminor(inode)];
}