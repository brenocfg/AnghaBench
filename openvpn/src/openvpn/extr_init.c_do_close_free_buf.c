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
struct TYPE_2__ {int buffers_owned; int /*<<< orphan*/ * buffers; } ;
struct context {TYPE_1__ c2; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_context_buffers (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
do_close_free_buf(struct context *c)
{
    if (c->c2.buffers_owned)
    {
        free_context_buffers(c->c2.buffers);
        c->c2.buffers = NULL;
        c->c2.buffers_owned = false;
    }
}