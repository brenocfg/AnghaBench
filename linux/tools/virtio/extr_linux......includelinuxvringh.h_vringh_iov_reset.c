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
struct vringh_iov {size_t i; scalar_t__ consumed; TYPE_1__* iov; } ;
struct TYPE_2__ {int /*<<< orphan*/  iov_base; int /*<<< orphan*/  iov_len; } ;

/* Variables and functions */

__attribute__((used)) static inline void vringh_iov_reset(struct vringh_iov *iov)
{
	iov->iov[iov->i].iov_len += iov->consumed;
	iov->iov[iov->i].iov_base -= iov->consumed;
	iov->consumed = 0;
	iov->i = 0;
}