#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jsstr_t ;
struct TYPE_4__ {TYPE_1__* func_code; } ;
struct TYPE_3__ {int /*<<< orphan*/  source_len; int /*<<< orphan*/  source; } ;
typedef  TYPE_2__ InterpretedFunction ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  FunctionInstance ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/ * jsstr_alloc_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT InterpretedFunction_toString(FunctionInstance *func, jsstr_t **ret)
{
    InterpretedFunction *function = (InterpretedFunction*)func;

    *ret = jsstr_alloc_len(function->func_code->source, function->func_code->source_len);
    return *ret ? S_OK : E_OUTOFMEMORY;
}