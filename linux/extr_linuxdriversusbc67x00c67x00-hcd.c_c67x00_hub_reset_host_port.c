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
struct c67x00_sie {int /*<<< orphan*/  dev; struct c67x00_hcd* private_data; } ;
struct c67x00_hcd {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_EOT ; 
 int /*<<< orphan*/  c67x00_ll_husb_reset (struct c67x00_sie*,int) ; 
 int /*<<< orphan*/  c67x00_ll_husb_reset_port (struct c67x00_sie*,int) ; 
 int /*<<< orphan*/  c67x00_ll_set_husb_eot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void c67x00_hub_reset_host_port(struct c67x00_sie *sie, int port)
{
	struct c67x00_hcd *c67x00 = sie->private_data;
	unsigned long flags;

	c67x00_ll_husb_reset(sie, port);

	spin_lock_irqsave(&c67x00->lock, flags);
	c67x00_ll_husb_reset_port(sie, port);
	spin_unlock_irqrestore(&c67x00->lock, flags);

	c67x00_ll_set_husb_eot(sie->dev, DEFAULT_EOT);
}