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
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
struct TYPE_4__ {int /*<<< orphan*/  str; } ;
typedef  TYPE_1__ StringInstance ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_jsstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * jsstr_substr (int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  jsval_string (int /*<<< orphan*/ *) ; 
 TYPE_1__* string_from_jsdisp (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT String_idx_get(jsdisp_t *jsdisp, unsigned idx, jsval_t *r)
{
    StringInstance *string = string_from_jsdisp(jsdisp);
    jsstr_t *ret;

    ret = jsstr_substr(string->str, idx, 1);
    if(!ret)
        return E_OUTOFMEMORY;

    TRACE("%p[%u] = %s\n", string, idx, debugstr_jsstr(ret));

    *r = jsval_string(ret);
    return S_OK;
}