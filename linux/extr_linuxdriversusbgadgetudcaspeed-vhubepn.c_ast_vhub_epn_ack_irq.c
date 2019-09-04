#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ desc_mode; } ;
struct ast_vhub_ep {TYPE_1__ epn; } ;

/* Variables and functions */
 int /*<<< orphan*/  ast_vhub_epn_handle_ack (struct ast_vhub_ep*) ; 
 int /*<<< orphan*/  ast_vhub_epn_handle_ack_desc (struct ast_vhub_ep*) ; 

void ast_vhub_epn_ack_irq(struct ast_vhub_ep *ep)
{
	if (ep->epn.desc_mode)
		ast_vhub_epn_handle_ack_desc(ep);
	else
		ast_vhub_epn_handle_ack(ep);
}