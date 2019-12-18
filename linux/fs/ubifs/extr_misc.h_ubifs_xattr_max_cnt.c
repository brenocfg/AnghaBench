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
struct ubifs_info {int leb_size; int max_orphans; } ;

/* Variables and functions */
 int UBIFS_INO_NODE_SZ ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int) ; 

__attribute__((used)) static inline int ubifs_xattr_max_cnt(struct ubifs_info *c)
{
	int max_xattrs = (c->leb_size / 2) / UBIFS_INO_NODE_SZ;

	ubifs_assert(c, max_xattrs < c->max_orphans);
	return max_xattrs;
}