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
struct ctlr_info {scalar_t__ vaddr; } ;
struct CommandList {int /*<<< orphan*/  busaddr; } ;

/* Variables and functions */
 scalar_t__ SA5_REQUEST_PORT_OFFSET ; 
 scalar_t__ SA5_SCRATCHPAD_OFFSET ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void SA5_submit_command(struct ctlr_info *h,
	struct CommandList *c)
{
	writel(c->busaddr, h->vaddr + SA5_REQUEST_PORT_OFFSET);
	(void) readl(h->vaddr + SA5_SCRATCHPAD_OFFSET);
}