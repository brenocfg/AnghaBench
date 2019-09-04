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
typedef  int u64 ;

/* Variables and functions */
 int /*<<< orphan*/  pr_warn_ratelimited (char*,int,char const*,int,int) ; 

__attribute__((used)) static u64 ovl_remap_lower_ino(u64 ino, int xinobits, int fsid,
			       const char *name, int namelen)
{
	if (ino >> (64 - xinobits)) {
		pr_warn_ratelimited("overlayfs: d_ino too big (%.*s, ino=%llu, xinobits=%d)\n",
				    namelen, name, ino, xinobits);
		return ino;
	}

	return ino | ((u64)fsid) << (64 - xinobits);
}