#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  statbar_ctx_id; int /*<<< orphan*/  statbar; } ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_STATUSBAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_statusbar_pop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_gtk__is_active_context (TYPE_1__*) ; 
 TYPE_1__* pgctx ; 

__attribute__((used)) static void gtk_helpline_pop(void)
{
	if (!perf_gtk__is_active_context(pgctx))
		return;

	gtk_statusbar_pop(GTK_STATUSBAR(pgctx->statbar),
			  pgctx->statbar_ctx_id);
}