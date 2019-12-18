#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jsdisp_t ;
struct TYPE_3__ {int /*<<< orphan*/  item; } ;
typedef  TYPE_1__ EnumeratorInstance ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*) ; 
 TYPE_1__* enumerator_from_jsdisp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Enumerator_destructor(jsdisp_t *dispex)
{
    EnumeratorInstance *This = enumerator_from_jsdisp(dispex);

    TRACE("\n");

    jsval_release(This->item);
    heap_free(dispex);
}