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
struct xdp_umem {int /*<<< orphan*/ * pgs; int /*<<< orphan*/  npgs; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_user_pages_dirty_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void xdp_umem_unpin_pages(struct xdp_umem *umem)
{
	put_user_pages_dirty_lock(umem->pgs, umem->npgs, true);

	kfree(umem->pgs);
	umem->pgs = NULL;
}