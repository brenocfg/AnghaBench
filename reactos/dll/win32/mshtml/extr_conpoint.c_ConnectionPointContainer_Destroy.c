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
struct TYPE_5__ {scalar_t__ cps; TYPE_1__* cp_entries; } ;
struct TYPE_4__ {scalar_t__ riid; } ;
typedef  TYPE_2__ ConnectionPointContainer ;

/* Variables and functions */
 int /*<<< orphan*/  ConnectionPoint_Destroy (scalar_t__) ; 
 int /*<<< orphan*/  heap_free (scalar_t__) ; 

void ConnectionPointContainer_Destroy(ConnectionPointContainer *This)
{
    unsigned i;

    if(!This->cps)
        return;

    for(i=0; This->cp_entries[i].riid; i++)
        ConnectionPoint_Destroy(This->cps+i);
    heap_free(This->cps);
}