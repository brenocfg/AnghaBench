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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct fuse_file {TYPE_1__ readdir; struct fuse_file* release_args; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct fuse_file*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

void fuse_file_free(struct fuse_file *ff)
{
	kfree(ff->release_args);
	mutex_destroy(&ff->readdir.lock);
	kfree(ff);
}