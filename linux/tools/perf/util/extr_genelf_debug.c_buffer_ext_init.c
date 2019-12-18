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
struct buffer_ext {scalar_t__ max_sz; scalar_t__ cur_pos; int /*<<< orphan*/ * data; } ;

/* Variables and functions */

__attribute__((used)) static void
buffer_ext_init(struct buffer_ext *be)
{
	be->data = NULL;
	be->cur_pos = 0;
	be->max_sz = 0;
}