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
struct p9_fid {int /*<<< orphan*/  dlist; } ;
struct hlist_head {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_fsdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,struct hlist_head*) ; 

__attribute__((used)) static inline void __add_fid(struct dentry *dentry, struct p9_fid *fid)
{
	hlist_add_head(&fid->dlist, (struct hlist_head *)&dentry->d_fsdata);
}