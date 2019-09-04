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
typedef  int /*<<< orphan*/  u8 ;
struct tc35815_local {scalar_t__ fd_buf; scalar_t__ fd_buf_dma; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */

__attribute__((used)) static inline dma_addr_t fd_virt_to_bus(struct tc35815_local *lp, void *virt)
{
	return lp->fd_buf_dma + ((u8 *)virt - (u8 *)lp->fd_buf);
}