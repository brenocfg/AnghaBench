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
typedef  int /*<<< orphan*/  u32 ;
struct wil6210_priv {scalar_t__ csr; } ;

/* Variables and functions */
 scalar_t__ HOSTADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void wil_w(struct wil6210_priv *wil, u32 reg, u32 val)
{
	writel(val, wil->csr + HOSTADDR(reg));
	wmb(); /* wait for write to propagate to the HW */
}