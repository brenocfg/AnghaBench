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
typedef  int /*<<< orphan*/  u64 ;
struct fuse_entry_out {int /*<<< orphan*/  attr_valid_nsec; int /*<<< orphan*/  attr_valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  time_to_jiffies (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 entry_attr_timeout(struct fuse_entry_out *o)
{
	return time_to_jiffies(o->attr_valid, o->attr_valid_nsec);
}