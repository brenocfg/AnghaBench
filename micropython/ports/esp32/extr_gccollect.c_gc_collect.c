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

/* Variables and functions */
 int /*<<< orphan*/  gc_collect_end () ; 
 int /*<<< orphan*/  gc_collect_inner (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gc_collect_start () ; 

void gc_collect(void) {
    gc_collect_start();
    gc_collect_inner(0);
    gc_collect_end();
}