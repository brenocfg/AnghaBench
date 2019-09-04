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
struct cxgbi_sock {TYPE_1__* cdev; } ;
struct TYPE_2__ {int nmtus; unsigned short* mtus; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int cxgbi_sock_find_best_mtu(struct cxgbi_sock *csk,
					     unsigned short mtu)
{
	int i = 0;

	while (i < csk->cdev->nmtus - 1 && csk->cdev->mtus[i + 1] <= mtu)
		++i;

	return i;
}