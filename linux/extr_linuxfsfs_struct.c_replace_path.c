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
struct path {scalar_t__ dentry; scalar_t__ mnt; } ;

/* Variables and functions */
 scalar_t__ likely (int) ; 

__attribute__((used)) static inline int replace_path(struct path *p, const struct path *old, const struct path *new)
{
	if (likely(p->dentry != old->dentry || p->mnt != old->mnt))
		return 0;
	*p = *new;
	return 1;
}