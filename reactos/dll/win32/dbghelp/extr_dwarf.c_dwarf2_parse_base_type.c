#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct symt {int dummy; } ;
struct TYPE_13__ {int uvalue; int /*<<< orphan*/ * string; } ;
struct attribute {TYPE_1__ u; } ;
typedef  enum BasicType { ____Placeholder_BasicType } BasicType ;
struct TYPE_14__ {struct symt** symt_cache; int /*<<< orphan*/  module; } ;
typedef  TYPE_2__ dwarf2_parse_context_t ;
struct TYPE_15__ {struct symt* symt; } ;
typedef  TYPE_3__ dwarf2_debug_info_t ;
struct TYPE_16__ {struct symt symt; } ;

/* Variables and functions */
#define  DW_ATE_address 138 
#define  DW_ATE_boolean 137 
#define  DW_ATE_complex_float 136 
#define  DW_ATE_float 135 
#define  DW_ATE_signed 134 
#define  DW_ATE_signed_char 133 
#define  DW_ATE_unsigned 132 
#define  DW_ATE_unsigned_char 131 
#define  DW_ATE_void 130 
 int /*<<< orphan*/  DW_AT_byte_size ; 
 int /*<<< orphan*/  DW_AT_encoding ; 
 int /*<<< orphan*/  DW_AT_name ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int btBool ; 
 int btChar ; 
 int btComplex ; 
 int btFloat ; 
#define  btInt 129 
 int btNoType ; 
 int btUInt ; 
 int btULong ; 
#define  btVoid 128 
 int /*<<< orphan*/  dwarf2_debug_ctx (TYPE_2__*) ; 
 int /*<<< orphan*/  dwarf2_debug_di (TYPE_3__*) ; 
 int /*<<< orphan*/  dwarf2_find_attribute (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ,struct attribute*) ; 
 scalar_t__ dwarf2_get_di_children (TYPE_2__*,TYPE_3__*) ; 
 int sc_int1 ; 
 int sc_int2 ; 
 int sc_int4 ; 
 int sc_void ; 
 TYPE_4__* symt_new_basic (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct symt* dwarf2_parse_base_type(dwarf2_parse_context_t* ctx,
                                           dwarf2_debug_info_t* di)
{
    struct attribute name;
    struct attribute size;
    struct attribute encoding;
    enum BasicType bt;
    int cache_idx = -1;
    if (di->symt) return di->symt;

    TRACE("%s, for %s\n", dwarf2_debug_ctx(ctx), dwarf2_debug_di(di)); 

    if (!dwarf2_find_attribute(ctx, di, DW_AT_name, &name))
        name.u.string = NULL;
    if (!dwarf2_find_attribute(ctx, di, DW_AT_byte_size, &size)) size.u.uvalue = 0;
    if (!dwarf2_find_attribute(ctx, di, DW_AT_encoding, &encoding)) encoding.u.uvalue = DW_ATE_void;

    switch (encoding.u.uvalue)
    {
    case DW_ATE_void:           bt = btVoid; break;
    case DW_ATE_address:        bt = btULong; break;
    case DW_ATE_boolean:        bt = btBool; break;
    case DW_ATE_complex_float:  bt = btComplex; break;
    case DW_ATE_float:          bt = btFloat; break;
    case DW_ATE_signed:         bt = btInt; break;
    case DW_ATE_unsigned:       bt = btUInt; break;
    case DW_ATE_signed_char:    bt = btChar; break;
    case DW_ATE_unsigned_char:  bt = btChar; break;
    default:                    bt = btNoType; break;
    }
    di->symt = &symt_new_basic(ctx->module, bt, name.u.string, size.u.uvalue)->symt;
    switch (bt)
    {
    case btVoid:
        assert(size.u.uvalue == 0);
        cache_idx = sc_void;
        break;
    case btInt:
        switch (size.u.uvalue)
        {
        case 1: cache_idx = sc_int1; break;
        case 2: cache_idx = sc_int2; break;
        case 4: cache_idx = sc_int4; break;
        }
        break;
    default: break;
    }
    if (cache_idx != -1 && !ctx->symt_cache[cache_idx])
        ctx->symt_cache[cache_idx] = di->symt;

    if (dwarf2_get_di_children(ctx, di)) FIXME("Unsupported children\n");
    return di->symt;
}