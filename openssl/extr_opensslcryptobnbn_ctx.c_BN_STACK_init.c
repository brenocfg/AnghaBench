#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ size; scalar_t__ depth; int /*<<< orphan*/ * indexes; } ;
typedef  TYPE_1__ BN_STACK ;

/* Variables and functions */

__attribute__((used)) static void BN_STACK_init(BN_STACK *st)
{
    st->indexes = NULL;
    st->depth = st->size = 0;
}