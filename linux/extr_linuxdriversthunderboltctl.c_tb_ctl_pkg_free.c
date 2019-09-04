#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  buffer_phy; } ;
struct ctl_pkg {TYPE_2__ frame; int /*<<< orphan*/  buffer; TYPE_1__* ctl; } ;
struct TYPE_3__ {int /*<<< orphan*/  frame_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ctl_pkg*) ; 

__attribute__((used)) static void tb_ctl_pkg_free(struct ctl_pkg *pkg)
{
	if (pkg) {
		dma_pool_free(pkg->ctl->frame_pool,
			      pkg->buffer, pkg->frame.buffer_phy);
		kfree(pkg);
	}
}