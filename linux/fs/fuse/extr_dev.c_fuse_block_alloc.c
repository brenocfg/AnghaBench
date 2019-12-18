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
struct fuse_conn {scalar_t__ blocked; int /*<<< orphan*/  initialized; } ;

/* Variables and functions */

__attribute__((used)) static bool fuse_block_alloc(struct fuse_conn *fc, bool for_background)
{
	return !fc->initialized || (for_background && fc->blocked);
}