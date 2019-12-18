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
typedef  int /*<<< orphan*/  event_target_t ;
struct TYPE_5__ {TYPE_1__* doc; } ;
struct TYPE_4__ {int /*<<< orphan*/ * body_event_target; } ;
typedef  TYPE_2__ HTMLInnerWindow ;
typedef  int /*<<< orphan*/  DispatchEx ;

/* Variables and functions */
 TYPE_2__* impl_from_DispatchEx (int /*<<< orphan*/ *) ; 

__attribute__((used)) static event_target_t **HTMLWindow_get_event_target_ptr(DispatchEx *dispex)
{
    HTMLInnerWindow *This = impl_from_DispatchEx(dispex);
    return &This->doc->body_event_target;
}