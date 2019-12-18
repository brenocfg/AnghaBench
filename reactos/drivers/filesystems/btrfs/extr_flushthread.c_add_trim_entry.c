#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint64_t ;
struct TYPE_5__ {int /*<<< orphan*/  list_entry; void* size; void* address; } ;
typedef  TYPE_1__ space ;
struct TYPE_6__ {int /*<<< orphan*/  trim_list; int /*<<< orphan*/  num_trim_entries; } ;
typedef  TYPE_2__ device ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_TAG ; 
 int /*<<< orphan*/  ERR (char*) ; 
 TYPE_1__* ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InsertTailList (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PagedPool ; 

__attribute__((used)) static void add_trim_entry(device* dev, uint64_t address, uint64_t size) {
    space* s = ExAllocatePoolWithTag(PagedPool, sizeof(space), ALLOC_TAG);
    if (!s) {
        ERR("out of memory\n");
        return;
    }

    s->address = address;
    s->size = size;
    dev->num_trim_entries++;

    InsertTailList(&dev->trim_list, &s->list_entry);
}