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
typedef  void* uint64_t ;
struct TYPE_4__ {int /*<<< orphan*/ * chunk; void* length; void* address; int /*<<< orphan*/ * list_size; int /*<<< orphan*/ * list; } ;
typedef  TYPE_1__ rollback_space ;
typedef  int /*<<< orphan*/  chunk ;
typedef  int /*<<< orphan*/  LIST_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_TAG ; 
 int /*<<< orphan*/  ERR (char*) ; 
 TYPE_1__* ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PagedPool ; 
 int /*<<< orphan*/  ROLLBACK_ADD_SPACE ; 
 int /*<<< orphan*/  ROLLBACK_SUBTRACT_SPACE ; 
 int /*<<< orphan*/  add_rollback (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void add_rollback_space(LIST_ENTRY* rollback, bool add, LIST_ENTRY* list, LIST_ENTRY* list_size, uint64_t address, uint64_t length, chunk* c) {
    rollback_space* rs;

    rs = ExAllocatePoolWithTag(PagedPool, sizeof(rollback_space), ALLOC_TAG);
    if (!rs) {
        ERR("out of memory\n");
        return;
    }

    rs->list = list;
    rs->list_size = list_size;
    rs->address = address;
    rs->length = length;
    rs->chunk = c;

    add_rollback(rollback, add ? ROLLBACK_ADD_SPACE : ROLLBACK_SUBTRACT_SPACE, rs);
}