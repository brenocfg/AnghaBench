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
struct wkup_m3_ipc {scalar_t__ ipc_mem_base; } ;

/* Variables and functions */
 scalar_t__ AM33XX_CONTROL_M3_TXEV_EOI ; 
 int /*<<< orphan*/  AM33XX_M3_TXEV_ENABLE ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void am33xx_txev_enable(struct wkup_m3_ipc *m3_ipc)
{
	writel(AM33XX_M3_TXEV_ENABLE,
	       m3_ipc->ipc_mem_base + AM33XX_CONTROL_M3_TXEV_EOI);
}