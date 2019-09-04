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
struct writeback_control {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int writeback_single_inode (struct inode*,struct writeback_control*) ; 

int sync_inode(struct inode *inode, struct writeback_control *wbc)
{
	return writeback_single_inode(inode, wbc);
}