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
typedef  int /*<<< orphan*/  script_ctx_t ;
struct TYPE_6__ {int /*<<< orphan*/  name; struct TYPE_6__* next; } ;
typedef  TYPE_1__ function_t ;
struct TYPE_7__ {int /*<<< orphan*/  name; struct TYPE_7__* next; } ;
typedef  TYPE_2__ dynamic_var_t ;
struct TYPE_8__ {TYPE_4__* classes; TYPE_1__* funcs; TYPE_2__* global_vars; } ;
typedef  TYPE_3__ compile_ctx_t ;
struct TYPE_9__ {int /*<<< orphan*/  name; struct TYPE_9__* next; } ;
typedef  TYPE_4__ class_desc_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 scalar_t__ lookup_script_identifier (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT check_script_collisions(compile_ctx_t *ctx, script_ctx_t *script)
{
    class_desc_t *class;
    dynamic_var_t *var;
    function_t *func;

    for(var = ctx->global_vars; var; var = var->next) {
        if(lookup_script_identifier(script, var->name)) {
            FIXME("%s: redefined\n", debugstr_w(var->name));
            return E_FAIL;
        }
    }

    for(func = ctx->funcs; func; func = func->next) {
        if(lookup_script_identifier(script, func->name)) {
            FIXME("%s: redefined\n", debugstr_w(func->name));
            return E_FAIL;
        }
    }

    for(class = ctx->classes; class; class = class->next) {
        if(lookup_script_identifier(script, class->name)) {
            FIXME("%s: redefined\n", debugstr_w(class->name));
            return E_FAIL;
        }
    }

    return S_OK;
}