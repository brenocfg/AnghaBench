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
typedef  int u8 ;
struct max63xx_wdt {int /*<<< orphan*/  lock; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int MAX6369_WDSET ; 
 int __raw_readb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writeb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void max63xx_mmap_set(struct max63xx_wdt *wdt, u8 set)
{
	u8 val;

	spin_lock(&wdt->lock);

	val = __raw_readb(wdt->base);
	val &= ~MAX6369_WDSET;
	val |= set & MAX6369_WDSET;
	__raw_writeb(val, wdt->base);

	spin_unlock(&wdt->lock);
}