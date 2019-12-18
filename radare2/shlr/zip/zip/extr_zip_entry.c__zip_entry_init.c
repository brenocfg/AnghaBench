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
struct zip_entry {scalar_t__ deleted; int /*<<< orphan*/ * source; int /*<<< orphan*/ * changes; int /*<<< orphan*/ * orig; } ;

/* Variables and functions */

void
_zip_entry_init(struct zip_entry *e)
{
    e->orig = NULL;
    e->changes = NULL;
    e->source = NULL;
    e->deleted = 0;
}