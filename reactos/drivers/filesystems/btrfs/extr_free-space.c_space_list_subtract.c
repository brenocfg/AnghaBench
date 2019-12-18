#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_4__ {int changed; int space_changed; int /*<<< orphan*/  space_size; int /*<<< orphan*/  space; int /*<<< orphan*/  deleting; } ;
typedef  TYPE_1__ chunk ;
typedef  int /*<<< orphan*/  LIST_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  space_list_subtract2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 

void space_list_subtract(chunk* c, bool deleting, uint64_t address, uint64_t length, LIST_ENTRY* rollback) {
    LIST_ENTRY* list;

    list = deleting ? &c->deleting : &c->space;

    c->changed = true;
    c->space_changed = true;

    space_list_subtract2(list, deleting ? NULL : &c->space_size, address, length, c, rollback);
}