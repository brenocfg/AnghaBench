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
struct path {TYPE_2__* dentry; } ;
typedef  scalar_t__ dev_t ;
struct TYPE_4__ {TYPE_1__* d_sb; } ;
struct TYPE_3__ {scalar_t__ s_dev; } ;

/* Variables and functions */

__attribute__((used)) static int test_by_dev(const struct path *path, void *p)
{
	return path->dentry->d_sb->s_dev == *(dev_t *)p;
}