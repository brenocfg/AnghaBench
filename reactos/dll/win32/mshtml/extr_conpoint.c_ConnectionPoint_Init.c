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
typedef  int /*<<< orphan*/  cp_static_data_t ;
struct TYPE_4__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_5__ {int /*<<< orphan*/ * data; int /*<<< orphan*/  iid; scalar_t__ sinks_size; int /*<<< orphan*/ * sinks; int /*<<< orphan*/ * container; TYPE_1__ IConnectionPoint_iface; } ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  int /*<<< orphan*/  ConnectionPointContainer ;
typedef  TYPE_2__ ConnectionPoint ;

/* Variables and functions */
 int /*<<< orphan*/  ConnectionPointVtbl ; 

__attribute__((used)) static void ConnectionPoint_Init(ConnectionPoint *cp, ConnectionPointContainer *container, REFIID riid, cp_static_data_t *data)
{
    cp->IConnectionPoint_iface.lpVtbl = &ConnectionPointVtbl;
    cp->container = container;
    cp->sinks = NULL;
    cp->sinks_size = 0;
    cp->iid = riid;
    cp->data = data;
}