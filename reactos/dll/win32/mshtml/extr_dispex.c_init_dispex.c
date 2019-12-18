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
typedef  int /*<<< orphan*/  dispex_static_data_t ;
struct TYPE_4__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_5__ {int /*<<< orphan*/ * dynamic_data; int /*<<< orphan*/ * data; int /*<<< orphan*/ * outer; TYPE_1__ IDispatchEx_iface; } ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  TYPE_2__ DispatchEx ;

/* Variables and functions */
 int /*<<< orphan*/  DispatchExVtbl ; 

void init_dispex(DispatchEx *dispex, IUnknown *outer, dispex_static_data_t *data)
{
    dispex->IDispatchEx_iface.lpVtbl = &DispatchExVtbl;
    dispex->outer = outer;
    dispex->data = data;
    dispex->dynamic_data = NULL;
}