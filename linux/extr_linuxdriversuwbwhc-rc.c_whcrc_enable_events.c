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
typedef  int u32 ;
struct whcrc {int /*<<< orphan*/  irq_lock; scalar_t__ rc_base; int /*<<< orphan*/  evt_dma_buf; } ;

/* Variables and functions */
 scalar_t__ URCCMD ; 
 int URCCMD_ACTIVE ; 
 int URCCMD_EARV ; 
 scalar_t__ URCEVTADDR ; 
 int le_readl (scalar_t__) ; 
 int /*<<< orphan*/  le_writel (int,scalar_t__) ; 
 int /*<<< orphan*/  le_writeq (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
void whcrc_enable_events(struct whcrc *whcrc)
{
	u32 urccmd;

	le_writeq(whcrc->evt_dma_buf, whcrc->rc_base + URCEVTADDR);

	spin_lock(&whcrc->irq_lock);
	urccmd = le_readl(whcrc->rc_base + URCCMD) & ~URCCMD_ACTIVE;
	le_writel(urccmd | URCCMD_EARV, whcrc->rc_base + URCCMD);
	spin_unlock(&whcrc->irq_lock);
}