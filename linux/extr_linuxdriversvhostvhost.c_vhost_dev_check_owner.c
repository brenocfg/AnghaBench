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
struct vhost_dev {scalar_t__ mm; } ;
struct TYPE_2__ {scalar_t__ mm; } ;

/* Variables and functions */
 long EPERM ; 
 TYPE_1__* current ; 

long vhost_dev_check_owner(struct vhost_dev *dev)
{
	/* Are you the owner? If not, I don't think you mean to do that */
	return dev->mm == current->mm ? 0 : -EPERM;
}