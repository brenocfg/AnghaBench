#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  jsval_t ;

/* Variables and functions */
 int /*<<< orphan*/  IDispatch_Release (int /*<<< orphan*/ ) ; 
#define  JSV_OBJECT 130 
#define  JSV_STRING 129 
#define  JSV_VARIANT 128 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_variant (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsstr_release (int /*<<< orphan*/ ) ; 
 int jsval_type (int /*<<< orphan*/ ) ; 

void jsval_release(jsval_t val)
{
    switch(jsval_type(val)) {
    case JSV_OBJECT:
        if(get_object(val))
            IDispatch_Release(get_object(val));
        break;
    case JSV_STRING:
        jsstr_release(get_string(val));
        break;
    case JSV_VARIANT:
        VariantClear(get_variant(val));
        heap_free(get_variant(val));
        break;
    default:
        break;
    }
}