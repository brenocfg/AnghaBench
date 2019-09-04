#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * next; } ;
struct fuse_iqueue {TYPE_1__ forget_list_head; } ;

/* Variables and functions */

__attribute__((used)) static int forget_pending(struct fuse_iqueue *fiq)
{
	return fiq->forget_list_head.next != NULL;
}