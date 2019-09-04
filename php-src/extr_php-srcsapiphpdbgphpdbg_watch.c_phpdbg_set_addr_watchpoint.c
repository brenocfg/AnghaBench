#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* ptr; } ;
struct TYPE_5__ {size_t size; int /*<<< orphan*/  elements; int /*<<< orphan*/ * coll; int /*<<< orphan*/ * ref; TYPE_1__ addr; } ;
typedef  TYPE_2__ phpdbg_watchpoint_t ;

/* Variables and functions */
 int /*<<< orphan*/  brml ; 
 int /*<<< orphan*/  zend_hash_init (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void phpdbg_set_addr_watchpoint(void *addr, size_t size, phpdbg_watchpoint_t *watch) {
	watch->addr.ptr = addr;
	watch->size = size;
	watch->ref = NULL;
	watch->coll = NULL;
	zend_hash_init(&watch->elements, 8, brml, NULL, 0);
}