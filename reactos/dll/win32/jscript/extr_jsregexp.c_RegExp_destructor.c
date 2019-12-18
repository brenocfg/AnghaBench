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
struct TYPE_4__ {int /*<<< orphan*/  str; int /*<<< orphan*/  last_index_val; scalar_t__ jsregexp; } ;
typedef  TYPE_1__ RegExpInstance ;

/* Variables and functions */
 int /*<<< orphan*/  heap_free (TYPE_1__*) ; 
 int /*<<< orphan*/  jsstr_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regexp_destroy (scalar_t__) ; 
 TYPE_1__* regexp_from_jsdisp (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void RegExp_destructor(jsdisp_t *dispex)
{
    RegExpInstance *This = regexp_from_jsdisp(dispex);

    if(This->jsregexp)
        regexp_destroy(This->jsregexp);
    jsval_release(This->last_index_val);
    jsstr_release(This->str);
    heap_free(This);
}