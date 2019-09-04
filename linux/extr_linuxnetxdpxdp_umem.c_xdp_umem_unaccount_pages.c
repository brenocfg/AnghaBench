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
struct xdp_umem {TYPE_1__* user; int /*<<< orphan*/  npgs; } ;
struct TYPE_2__ {int /*<<< orphan*/  locked_vm; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_long_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_uid (TYPE_1__*) ; 

__attribute__((used)) static void xdp_umem_unaccount_pages(struct xdp_umem *umem)
{
	if (umem->user) {
		atomic_long_sub(umem->npgs, &umem->user->locked_vm);
		free_uid(umem->user);
	}
}