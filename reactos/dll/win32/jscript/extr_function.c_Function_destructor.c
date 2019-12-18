#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jsdisp_t ;
struct TYPE_7__ {TYPE_1__* vtbl; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* destructor ) (TYPE_2__*) ;} ;
typedef  TYPE_2__ FunctionInstance ;

/* Variables and functions */
 TYPE_2__* function_from_jsdisp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_free (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static void Function_destructor(jsdisp_t *dispex)
{
    FunctionInstance *function = function_from_jsdisp(dispex);
    function->vtbl->destructor(function);
    heap_free(function);
}