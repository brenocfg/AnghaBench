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
struct fuse_iqueue {int /*<<< orphan*/  reqctr; } ;

/* Variables and functions */

__attribute__((used)) static u64 fuse_get_unique(struct fuse_iqueue *fiq)
{
	return ++fiq->reqctr;
}