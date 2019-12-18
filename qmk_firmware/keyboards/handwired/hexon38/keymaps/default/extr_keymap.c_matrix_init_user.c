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
struct TYPE_2__ {int ifirst; int ilast; int /*<<< orphan*/ * head; scalar_t__ count; } ;

/* Variables and functions */
 TYPE_1__ g_pending ; 

void matrix_init_user(void) {
    g_pending.ifirst = -1;
    g_pending.ilast = -1;
    g_pending.count = 0;
    g_pending.head = NULL;
}