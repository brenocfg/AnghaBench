#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xlog {TYPE_2__* l_cilp; } ;
struct TYPE_4__ {TYPE_1__* xc_ctx; } ;
struct TYPE_3__ {int sequence; int /*<<< orphan*/  ticket; } ;

/* Variables and functions */
 int /*<<< orphan*/  xlog_cil_ticket_alloc (struct xlog*) ; 

void
xlog_cil_init_post_recovery(
	struct xlog	*log)
{
	log->l_cilp->xc_ctx->ticket = xlog_cil_ticket_alloc(log);
	log->l_cilp->xc_ctx->sequence = 1;
}