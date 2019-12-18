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
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  d_invalidate (struct dentry*) ; 
 int /*<<< orphan*/  fuse_invalidate_entry_cache (struct dentry*) ; 

__attribute__((used)) static void fuse_invalidate_entry(struct dentry *entry)
{
	d_invalidate(entry);
	fuse_invalidate_entry_cache(entry);
}