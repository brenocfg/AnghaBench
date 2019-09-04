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
struct p9_fid {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 struct p9_fid* clone_fid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v9fs_fid_lookup (struct dentry*) ; 

__attribute__((used)) static inline struct p9_fid *v9fs_fid_clone(struct dentry *dentry)
{
	return clone_fid(v9fs_fid_lookup(dentry));
}