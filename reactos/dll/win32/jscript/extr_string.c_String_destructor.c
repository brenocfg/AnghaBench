#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jsdisp_t ;
struct TYPE_4__ {int /*<<< orphan*/  str; } ;
typedef  TYPE_1__ StringInstance ;

/* Variables and functions */
 int /*<<< orphan*/  heap_free (TYPE_1__*) ; 
 int /*<<< orphan*/  jsstr_release (int /*<<< orphan*/ ) ; 
 TYPE_1__* string_from_jsdisp (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void String_destructor(jsdisp_t *dispex)
{
    StringInstance *This = string_from_jsdisp(dispex);

    jsstr_release(This->str);
    heap_free(This);
}