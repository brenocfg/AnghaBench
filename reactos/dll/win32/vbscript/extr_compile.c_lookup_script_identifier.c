#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_4__* classes; TYPE_2__* global_funcs; TYPE_3__* global_vars; } ;
typedef  TYPE_1__ script_ctx_t ;
struct TYPE_7__ {int /*<<< orphan*/  name; struct TYPE_7__* next; } ;
typedef  TYPE_2__ function_t ;
struct TYPE_8__ {int /*<<< orphan*/  name; struct TYPE_8__* next; } ;
typedef  TYPE_3__ dynamic_var_t ;
struct TYPE_9__ {int /*<<< orphan*/  name; struct TYPE_9__* next; } ;
typedef  TYPE_4__ class_desc_t ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  strcmpiW (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static BOOL lookup_script_identifier(script_ctx_t *script, const WCHAR *identifier)
{
    class_desc_t *class;
    dynamic_var_t *var;
    function_t *func;

    for(var = script->global_vars; var; var = var->next) {
        if(!strcmpiW(var->name, identifier))
            return TRUE;
    }

    for(func = script->global_funcs; func; func = func->next) {
        if(!strcmpiW(func->name, identifier))
            return TRUE;
    }

    for(class = script->classes; class; class = class->next) {
        if(!strcmpiW(class->name, identifier))
            return TRUE;
    }

    return FALSE;
}