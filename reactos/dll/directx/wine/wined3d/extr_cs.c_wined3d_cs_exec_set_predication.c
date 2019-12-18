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
struct wined3d_cs_set_predication {int /*<<< orphan*/  value; int /*<<< orphan*/  predicate; } ;
struct TYPE_2__ {int /*<<< orphan*/  predicate_value; int /*<<< orphan*/  predicate; } ;
struct wined3d_cs {TYPE_1__ state; } ;

/* Variables and functions */

__attribute__((used)) static void wined3d_cs_exec_set_predication(struct wined3d_cs *cs, const void *data)
{
    const struct wined3d_cs_set_predication *op = data;

    cs->state.predicate = op->predicate;
    cs->state.predicate_value = op->value;
}