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
struct wined3d_cs_push_constants {int /*<<< orphan*/  constants; int /*<<< orphan*/  count; int /*<<< orphan*/  start_idx; int /*<<< orphan*/  type; } ;
struct wined3d_cs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  wined3d_cs_st_push_constants (struct wined3d_cs*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wined3d_cs_exec_push_constants(struct wined3d_cs *cs, const void *data)
{
    const struct wined3d_cs_push_constants *op = data;

    wined3d_cs_st_push_constants(cs, op->type, op->start_idx, op->count, op->constants);
}