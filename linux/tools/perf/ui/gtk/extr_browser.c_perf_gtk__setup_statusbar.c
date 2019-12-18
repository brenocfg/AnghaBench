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
struct TYPE_2__ {unsigned int statbar_ctx_id; int /*<<< orphan*/ * statbar; } ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_STATUSBAR (int /*<<< orphan*/ *) ; 
 unsigned int gtk_statusbar_get_context_id (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * gtk_statusbar_new () ; 
 TYPE_1__* pgctx ; 

GtkWidget *perf_gtk__setup_statusbar(void)
{
	GtkWidget *stbar;
	unsigned ctxid;

	stbar = gtk_statusbar_new();

	ctxid = gtk_statusbar_get_context_id(GTK_STATUSBAR(stbar),
					     "perf report");
	pgctx->statbar = stbar;
	pgctx->statbar_ctx_id = ctxid;

	return stbar;
}