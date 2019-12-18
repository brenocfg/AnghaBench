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
struct fuse_dev {int dummy; } ;
struct fuse_conn {int dummy; } ;

/* Variables and functions */
 struct fuse_dev* fuse_dev_alloc () ; 
 int /*<<< orphan*/  fuse_dev_install (struct fuse_dev*,struct fuse_conn*) ; 

struct fuse_dev *fuse_dev_alloc_install(struct fuse_conn *fc)
{
	struct fuse_dev *fud;

	fud = fuse_dev_alloc();
	if (!fud)
		return NULL;

	fuse_dev_install(fud, fc);
	return fud;
}