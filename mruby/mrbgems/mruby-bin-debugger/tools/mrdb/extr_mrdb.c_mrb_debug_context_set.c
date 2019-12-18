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
typedef  int /*<<< orphan*/  mrb_debug_context ;

/* Variables and functions */
 int /*<<< orphan*/ * _debug_context ; 

void
mrb_debug_context_set(mrb_debug_context *dbg)
{
  _debug_context = dbg;
}