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
struct tb_ctl {int /*<<< orphan*/  frame_pool; } ;
struct TYPE_2__ {int /*<<< orphan*/  buffer_phy; } ;
struct ctl_pkg {int /*<<< orphan*/  buffer; TYPE_1__ frame; struct tb_ctl* ctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dma_pool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ctl_pkg*) ; 
 struct ctl_pkg* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ctl_pkg *tb_ctl_pkg_alloc(struct tb_ctl *ctl)
{
	struct ctl_pkg *pkg = kzalloc(sizeof(*pkg), GFP_KERNEL);
	if (!pkg)
		return NULL;
	pkg->ctl = ctl;
	pkg->buffer = dma_pool_alloc(ctl->frame_pool, GFP_KERNEL,
				     &pkg->frame.buffer_phy);
	if (!pkg->buffer) {
		kfree(pkg);
		return NULL;
	}
	return pkg;
}