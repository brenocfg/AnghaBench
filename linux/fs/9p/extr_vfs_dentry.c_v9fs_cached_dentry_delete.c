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
 int /*<<< orphan*/  P9_DEBUG_VFS ; 
 scalar_t__ d_really_is_negative (struct dentry const*) ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*,struct dentry const*,struct dentry const*) ; 

__attribute__((used)) static int v9fs_cached_dentry_delete(const struct dentry *dentry)
{
	p9_debug(P9_DEBUG_VFS, " dentry: %pd (%p)\n",
		 dentry, dentry);

	/* Don't cache negative dentries */
	if (d_really_is_negative(dentry))
		return 1;
	return 0;
}