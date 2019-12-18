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
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_5__ {int ref; TYPE_2__ nsISimpleEnumerator_iface; int /*<<< orphan*/ * value; } ;
typedef  TYPE_1__ nsSingletonEnumerator ;
typedef  int /*<<< orphan*/  nsISupports ;
typedef  TYPE_2__ nsISimpleEnumerator ;

/* Variables and functions */
 TYPE_1__* heap_alloc (int) ; 
 int /*<<< orphan*/  nsISupports_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsSingletonEnumeratorVtbl ; 

__attribute__((used)) static nsISimpleEnumerator *create_singleton_enumerator(nsISupports *value)
{
    nsSingletonEnumerator *ret;

    ret = heap_alloc(sizeof(*ret));
    if(!ret)
        return NULL;

    ret->nsISimpleEnumerator_iface.lpVtbl = &nsSingletonEnumeratorVtbl;
    ret->ref = 1;

    if(value)
        nsISupports_AddRef(value);
    ret->value = value;
    return &ret->nsISimpleEnumerator_iface;
}