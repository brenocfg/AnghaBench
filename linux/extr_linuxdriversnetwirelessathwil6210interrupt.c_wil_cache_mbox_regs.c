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
struct TYPE_2__ {int /*<<< orphan*/  tx; int /*<<< orphan*/  rx; } ;
struct wil6210_priv {TYPE_1__ mbox_ctl; scalar_t__ csr; } ;
struct wil6210_mbox_ctl {int dummy; } ;

/* Variables and functions */
 scalar_t__ HOST_MBOX ; 
 int /*<<< orphan*/  wil_mbox_ring_le2cpus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wil_memcpy_fromio_32 (TYPE_1__*,scalar_t__,int) ; 

__attribute__((used)) static void wil_cache_mbox_regs(struct wil6210_priv *wil)
{
	/* make shadow copy of registers that should not change on run time */
	wil_memcpy_fromio_32(&wil->mbox_ctl, wil->csr + HOST_MBOX,
			     sizeof(struct wil6210_mbox_ctl));
	wil_mbox_ring_le2cpus(&wil->mbox_ctl.rx);
	wil_mbox_ring_le2cpus(&wil->mbox_ctl.tx);
}