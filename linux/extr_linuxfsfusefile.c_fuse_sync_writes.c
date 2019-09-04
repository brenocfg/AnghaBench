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
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fuse_release_nowrite (struct inode*) ; 
 int /*<<< orphan*/  fuse_set_nowrite (struct inode*) ; 

__attribute__((used)) static void fuse_sync_writes(struct inode *inode)
{
	fuse_set_nowrite(inode);
	fuse_release_nowrite(inode);
}