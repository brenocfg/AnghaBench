#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_14__ {int /*<<< orphan*/  mem_pool; } ;
typedef  TYPE_2__ njs_vm_t ;
typedef  int /*<<< orphan*/  njs_vm_event_t ;
struct TYPE_13__ {int length; int /*<<< orphan*/ * start; } ;
struct TYPE_15__ {int /*<<< orphan*/  pool; int /*<<< orphan*/ * proto; TYPE_1__ key; int /*<<< orphan*/  key_hash; } ;
typedef  TYPE_3__ njs_lvlhsh_query_t ;
typedef  scalar_t__ njs_int_t ;
typedef  TYPE_4__* njs_host_event_t ;
typedef  TYPE_5__* njs_external_ptr_t ;
struct TYPE_18__ {int /*<<< orphan*/ * prev; } ;
struct TYPE_16__ {TYPE_8__ link; int /*<<< orphan*/  vm_event; } ;
typedef  TYPE_4__ njs_ev_t ;
struct TYPE_17__ {int /*<<< orphan*/  events; TYPE_2__* vm; } ;
typedef  TYPE_5__ njs_console_t ;

/* Variables and functions */
 scalar_t__ NJS_OK ; 
 int /*<<< orphan*/  lvlhsh_proto ; 
 int /*<<< orphan*/  njs_djb_hash (int /*<<< orphan*/ *,int) ; 
 scalar_t__ njs_lvlhsh_delete (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  njs_mp_free (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  njs_queue_remove (TYPE_8__*) ; 
 int /*<<< orphan*/  njs_stderror (char*) ; 

__attribute__((used)) static void
njs_console_clear_timer(njs_external_ptr_t external, njs_host_event_t event)
{
    njs_vm_t            *vm;
    njs_ev_t            *ev;
    njs_int_t           ret;
    njs_console_t       *console;
    njs_lvlhsh_query_t  lhq;

    ev = event;
    console = external;
    vm = console->vm;

    lhq.key.start = (u_char *) &ev->vm_event;
    lhq.key.length = sizeof(njs_vm_event_t);
    lhq.key_hash = njs_djb_hash(lhq.key.start, lhq.key.length);

    lhq.proto = &lvlhsh_proto;
    lhq.pool = vm->mem_pool;

    if (ev->link.prev != NULL) {
        njs_queue_remove(&ev->link);
    }

    ret = njs_lvlhsh_delete(&console->events, &lhq);
    if (ret != NJS_OK) {
        njs_stderror("njs_lvlhsh_delete() failed\n");
    }

    njs_mp_free(vm->mem_pool, ev);
}