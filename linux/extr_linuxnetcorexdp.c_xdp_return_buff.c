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
struct xdp_buff {int /*<<< orphan*/  handle; TYPE_1__* rxq; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int /*<<< orphan*/  mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  __xdp_return (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

void xdp_return_buff(struct xdp_buff *xdp)
{
	__xdp_return(xdp->data, &xdp->rxq->mem, true, xdp->handle);
}