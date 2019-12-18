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
struct xdp_md {int dummy; } ;

/* Variables and functions */
 int bpf_redirect_map (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tx_port ; 

int xdp_redirect_map_2(struct xdp_md *xdp)
{
	return bpf_redirect_map(&tx_port, 2, 0);
}