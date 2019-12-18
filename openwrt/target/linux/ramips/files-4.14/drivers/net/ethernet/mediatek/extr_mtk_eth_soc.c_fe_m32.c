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
struct fe_priv {int /*<<< orphan*/  page_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __raw_readl (unsigned int) ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int fe_base ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void fe_m32(struct fe_priv *eth, u32 clear, u32 set, unsigned reg)
{
	u32 val;

	spin_lock(&eth->page_lock);
	val = __raw_readl(fe_base + reg);
	val &= ~clear;
	val |= set;
	__raw_writel(val, fe_base + reg);
	spin_unlock(&eth->page_lock);
}