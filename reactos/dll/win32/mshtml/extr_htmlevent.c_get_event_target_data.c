#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  event_target_t ;
struct TYPE_9__ {TYPE_2__* data; } ;
struct TYPE_8__ {int /*<<< orphan*/ * ptr; TYPE_4__ dispex; } ;
struct TYPE_7__ {TYPE_1__* vtbl; } ;
struct TYPE_6__ {int /*<<< orphan*/ ** (* get_event_target_ptr ) (TYPE_4__*) ;} ;
typedef  TYPE_3__ EventTarget ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/ * heap_alloc_zero (int) ; 
 int /*<<< orphan*/ ** stub1 (TYPE_4__*) ; 

__attribute__((used)) static inline event_target_t *get_event_target_data(EventTarget *event_target, BOOL alloc)
{
    event_target_t **ptr;

    ptr = event_target->dispex.data->vtbl && event_target->dispex.data->vtbl->get_event_target_ptr
        ? event_target->dispex.data->vtbl->get_event_target_ptr(&event_target->dispex)
        : &event_target->ptr;
    if(*ptr || !alloc)
        return *ptr;

    return *ptr = heap_alloc_zero(sizeof(event_target_t));
}