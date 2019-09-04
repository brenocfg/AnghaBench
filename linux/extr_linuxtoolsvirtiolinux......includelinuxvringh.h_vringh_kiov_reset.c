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
struct vringh_kiov {size_t i; scalar_t__ consumed; TYPE_1__* iov; } ;
struct TYPE_2__ {int /*<<< orphan*/  iov_base; int /*<<< orphan*/  iov_len; } ;

/* Variables and functions */

__attribute__((used)) static inline void vringh_kiov_reset(struct vringh_kiov *kiov)
{
	kiov->iov[kiov->i].iov_len += kiov->consumed;
	kiov->iov[kiov->i].iov_base -= kiov->consumed;
	kiov->consumed = 0;
	kiov->i = 0;
}