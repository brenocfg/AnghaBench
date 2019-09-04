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
typedef  int /*<<< orphan*/  runlist_element ;

/* Variables and functions */
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void ntfs_rl_mc(runlist_element *dstbase, int dst,
		runlist_element *srcbase, int src, int size)
{
	if (likely(size > 0))
		memcpy(dstbase + dst, srcbase + src, size * sizeof(*dstbase));
}