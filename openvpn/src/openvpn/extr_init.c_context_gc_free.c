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
struct TYPE_4__ {int /*<<< orphan*/  gc; } ;
struct TYPE_3__ {int /*<<< orphan*/  gc; } ;
struct context {int /*<<< orphan*/  gc; TYPE_2__ options; TYPE_1__ c2; } ;

/* Variables and functions */
 int /*<<< orphan*/  gc_free (int /*<<< orphan*/ *) ; 

void
context_gc_free(struct context *c)
{
    gc_free(&c->c2.gc);
    gc_free(&c->options.gc);
    gc_free(&c->gc);
}