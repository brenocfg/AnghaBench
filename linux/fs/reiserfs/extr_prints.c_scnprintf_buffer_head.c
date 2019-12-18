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
struct buffer_head {int /*<<< orphan*/  b_page; int /*<<< orphan*/  b_state; int /*<<< orphan*/  b_count; scalar_t__ b_blocknr; int /*<<< orphan*/  b_size; int /*<<< orphan*/  b_bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ buffer_dirty (struct buffer_head*) ; 
 scalar_t__ buffer_locked (struct buffer_head*) ; 
 scalar_t__ buffer_uptodate (struct buffer_head*) ; 
 int scnprintf (char*,size_t,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*) ; 

__attribute__((used)) static int scnprintf_buffer_head(char *buf, size_t size, struct buffer_head *bh)
{
	return scnprintf(buf, size,
			 "dev %pg, size %zd, blocknr %llu, count %d, state 0x%lx, page %p, (%s, %s, %s)",
			 bh->b_bdev, bh->b_size,
			 (unsigned long long)bh->b_blocknr,
			 atomic_read(&(bh->b_count)),
			 bh->b_state, bh->b_page,
			 buffer_uptodate(bh) ? "UPTODATE" : "!UPTODATE",
			 buffer_dirty(bh) ? "DIRTY" : "CLEAN",
			 buffer_locked(bh) ? "LOCKED" : "UNLOCKED");
}