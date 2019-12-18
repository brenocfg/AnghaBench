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
struct mount {int dummy; } ;

/* Variables and functions */
 int mnt_get_count (struct mount*) ; 

__attribute__((used)) static inline int do_refcount_check(struct mount *mnt, int count)
{
	return mnt_get_count(mnt) > count;
}