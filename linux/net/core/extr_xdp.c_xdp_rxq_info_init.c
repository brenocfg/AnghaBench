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
struct xdp_rxq_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct xdp_rxq_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void xdp_rxq_info_init(struct xdp_rxq_info *xdp_rxq)
{
	memset(xdp_rxq, 0, sizeof(*xdp_rxq));
}