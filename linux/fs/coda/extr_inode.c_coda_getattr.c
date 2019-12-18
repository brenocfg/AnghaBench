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
typedef  int /*<<< orphan*/  u32 ;
struct path {int /*<<< orphan*/  dentry; } ;
struct kstat {int dummy; } ;

/* Variables and functions */
 int coda_revalidate_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_fillattr (int /*<<< orphan*/ ,struct kstat*) ; 

int coda_getattr(const struct path *path, struct kstat *stat,
		 u32 request_mask, unsigned int flags)
{
	int err = coda_revalidate_inode(d_inode(path->dentry));
	if (!err)
		generic_fillattr(d_inode(path->dentry), stat);
	return err;
}