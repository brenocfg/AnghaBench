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
struct xdp_frame {int /*<<< orphan*/  mem; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  __xdp_return (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

void xdp_return_frame_rx_napi(struct xdp_frame *xdpf)
{
	__xdp_return(xdpf->data, &xdpf->mem, true, 0);
}