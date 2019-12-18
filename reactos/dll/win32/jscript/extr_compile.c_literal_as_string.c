#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  dval; int /*<<< orphan*/ * str; } ;
struct TYPE_5__ {int type; TYPE_1__ u; } ;
typedef  TYPE_2__ literal_t ;
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  int /*<<< orphan*/  compiler_ctx_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_UNREACHABLE ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
#define  LT_DOUBLE 129 
#define  LT_STRING 128 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  double_to_string (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static HRESULT literal_as_string(compiler_ctx_t *ctx, literal_t *literal, jsstr_t **str)
{
    switch(literal->type) {
    case LT_STRING:
        *str = literal->u.str;
        break;
    case LT_DOUBLE:
        return double_to_string(literal->u.dval, str);
    DEFAULT_UNREACHABLE;
    }

    return *str ? S_OK : E_OUTOFMEMORY;
}