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
struct perf_gtk_context {scalar_t__ main_window; } ;

/* Variables and functions */

__attribute__((used)) static inline bool perf_gtk__is_active_context(struct perf_gtk_context *ctx)
{
	return ctx && ctx->main_window;
}