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
struct path {TYPE_1__* dentry; int /*<<< orphan*/ * mnt; } ;
struct nameidata {int /*<<< orphan*/  m_seq; } ;
struct TYPE_2__ {int /*<<< orphan*/  d_seq; int /*<<< orphan*/  d_lockref; } ;

/* Variables and functions */
 int __legitimize_mnt (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockref_get_not_dead (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_seqcount_retry (int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool legitimize_path(struct nameidata *nd,
			    struct path *path, unsigned seq)
{
	int res = __legitimize_mnt(path->mnt, nd->m_seq);
	if (unlikely(res)) {
		if (res > 0)
			path->mnt = NULL;
		path->dentry = NULL;
		return false;
	}
	if (unlikely(!lockref_get_not_dead(&path->dentry->d_lockref))) {
		path->dentry = NULL;
		return false;
	}
	return !read_seqcount_retry(&path->dentry->d_seq, seq);
}