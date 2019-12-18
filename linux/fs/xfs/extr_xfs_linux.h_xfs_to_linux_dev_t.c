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
typedef  int /*<<< orphan*/  xfs_dev_t ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  MKDEV (int,int /*<<< orphan*/ ) ; 
 int sysv_major (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysv_minor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline dev_t xfs_to_linux_dev_t(xfs_dev_t dev)
{
	return MKDEV(sysv_major(dev) & 0x1ff, sysv_minor(dev));
}