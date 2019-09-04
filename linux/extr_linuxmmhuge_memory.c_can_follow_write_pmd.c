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
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 unsigned int FOLL_COW ; 
 unsigned int FOLL_FORCE ; 
 scalar_t__ pmd_dirty (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_write (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool can_follow_write_pmd(pmd_t pmd, unsigned int flags)
{
	return pmd_write(pmd) ||
	       ((flags & FOLL_FORCE) && (flags & FOLL_COW) && pmd_dirty(pmd));
}