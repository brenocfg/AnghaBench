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
struct nat_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HAS_FSYNCED_INODE ; 
 int /*<<< orphan*/  HAS_LAST_FSYNC ; 
 int /*<<< orphan*/  IS_CHECKPOINTED ; 
 int /*<<< orphan*/  set_nat_flag (struct nat_entry*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void nat_reset_flag(struct nat_entry *ne)
{
	/* these states can be set only after checkpoint was done */
	set_nat_flag(ne, IS_CHECKPOINTED, true);
	set_nat_flag(ne, HAS_FSYNCED_INODE, false);
	set_nat_flag(ne, HAS_LAST_FSYNC, true);
}