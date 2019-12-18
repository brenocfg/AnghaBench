#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* dentry; } ;
struct nameidata {int flags; TYPE_2__ root; int /*<<< orphan*/  root_seq; } ;
struct fs_struct {TYPE_2__ root; int /*<<< orphan*/  seq; } ;
struct TYPE_6__ {struct fs_struct* fs; } ;
struct TYPE_4__ {int /*<<< orphan*/  d_seq; } ;

/* Variables and functions */
 int LOOKUP_RCU ; 
 int LOOKUP_ROOT_GRABBED ; 
 int /*<<< orphan*/  __read_seqcount_begin (int /*<<< orphan*/ *) ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  get_fs_root (struct fs_struct*,TYPE_2__*) ; 
 unsigned int read_seqcount_begin (int /*<<< orphan*/ *) ; 
 scalar_t__ read_seqcount_retry (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void set_root(struct nameidata *nd)
{
	struct fs_struct *fs = current->fs;

	if (nd->flags & LOOKUP_RCU) {
		unsigned seq;

		do {
			seq = read_seqcount_begin(&fs->seq);
			nd->root = fs->root;
			nd->root_seq = __read_seqcount_begin(&nd->root.dentry->d_seq);
		} while (read_seqcount_retry(&fs->seq, seq));
	} else {
		get_fs_root(fs, &nd->root);
		nd->flags |= LOOKUP_ROOT_GRABBED;
	}
}