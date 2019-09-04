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
struct xdp_umem {int /*<<< orphan*/  work; int /*<<< orphan*/  users; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdp_umem_release_deferred ; 

void xdp_put_umem(struct xdp_umem *umem)
{
	if (!umem)
		return;

	if (refcount_dec_and_test(&umem->users)) {
		INIT_WORK(&umem->work, xdp_umem_release_deferred);
		schedule_work(&umem->work);
	}
}