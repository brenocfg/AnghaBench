#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  njs_vm_event_t ;
struct TYPE_5__ {int /*<<< orphan*/  start; } ;
struct TYPE_6__ {TYPE_1__ key; } ;
typedef  TYPE_2__ njs_lvlhsh_query_t ;
typedef  int /*<<< orphan*/  njs_int_t ;
struct TYPE_7__ {int /*<<< orphan*/  vm_event; } ;
typedef  TYPE_3__ njs_ev_t ;

/* Variables and functions */
 int /*<<< orphan*/  NJS_DECLINED ; 
 int /*<<< orphan*/  NJS_OK ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static njs_int_t
lvlhsh_key_test(njs_lvlhsh_query_t *lhq, void *data)
{
    njs_ev_t  *ev;

    ev = data;

    if (memcmp(&ev->vm_event, lhq->key.start, sizeof(njs_vm_event_t)) == 0) {
        return NJS_OK;
    }

    return NJS_DECLINED;
}