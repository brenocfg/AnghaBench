#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct fuse_file {TYPE_2__* fc; TYPE_1__* release_args; int /*<<< orphan*/  count; } ;
struct fuse_args {int /*<<< orphan*/  (* end ) (TYPE_2__*,struct fuse_args*,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {scalar_t__ no_open; scalar_t__ no_opendir; } ;
struct TYPE_5__ {struct fuse_args args; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOTCONN ; 
 int GFP_KERNEL ; 
 int __GFP_NOFAIL ; 
 int /*<<< orphan*/  fuse_release_end (TYPE_2__*,struct fuse_args*,int /*<<< orphan*/ ) ; 
 scalar_t__ fuse_simple_background (TYPE_2__*,struct fuse_args*,int) ; 
 int /*<<< orphan*/  fuse_simple_request (TYPE_2__*,struct fuse_args*) ; 
 int /*<<< orphan*/  kfree (struct fuse_file*) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fuse_file_put(struct fuse_file *ff, bool sync, bool isdir)
{
	if (refcount_dec_and_test(&ff->count)) {
		struct fuse_args *args = &ff->release_args->args;

		if (isdir ? ff->fc->no_opendir : ff->fc->no_open) {
			/* Do nothing when client does not implement 'open' */
			fuse_release_end(ff->fc, args, 0);
		} else if (sync) {
			fuse_simple_request(ff->fc, args);
			fuse_release_end(ff->fc, args, 0);
		} else {
			args->end = fuse_release_end;
			if (fuse_simple_background(ff->fc, args,
						   GFP_KERNEL | __GFP_NOFAIL))
				fuse_release_end(ff->fc, args, -ENOTCONN);
		}
		kfree(ff);
	}
}