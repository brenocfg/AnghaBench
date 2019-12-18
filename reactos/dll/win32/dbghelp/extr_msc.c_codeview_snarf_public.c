#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_12__ {int len; int id; } ;
struct TYPE_22__ {int /*<<< orphan*/  symtype; int /*<<< orphan*/  offset; int /*<<< orphan*/  segment; int /*<<< orphan*/  name; } ;
struct TYPE_21__ {int /*<<< orphan*/  symtype; int /*<<< orphan*/  offset; int /*<<< orphan*/  segment; int /*<<< orphan*/  p_name; } ;
struct TYPE_20__ {int /*<<< orphan*/  symtype; int /*<<< orphan*/  offset; int /*<<< orphan*/  segment; int /*<<< orphan*/  p_name; } ;
struct TYPE_19__ {int /*<<< orphan*/  symtype; int /*<<< orphan*/  offset; int /*<<< orphan*/  segment; int /*<<< orphan*/  name; } ;
struct TYPE_18__ {int /*<<< orphan*/  symtype; int /*<<< orphan*/  offset; int /*<<< orphan*/  segment; int /*<<< orphan*/  p_name; } ;
struct TYPE_17__ {int /*<<< orphan*/  symtype; int /*<<< orphan*/  offset; int /*<<< orphan*/  segment; int /*<<< orphan*/  p_name; } ;
struct TYPE_16__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  segment; int /*<<< orphan*/  symtype; int /*<<< orphan*/  name; } ;
struct TYPE_15__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  segment; int /*<<< orphan*/  p_name; } ;
struct TYPE_14__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  segment; int /*<<< orphan*/  symtype; int /*<<< orphan*/  p_name; } ;
union codeview_symbol {TYPE_10__ generic; TYPE_9__ thread_v3; TYPE_8__ thread_v2; TYPE_7__ thread_v1; TYPE_6__ data_v3; TYPE_5__ data_v2; TYPE_4__ data_v1; TYPE_3__ public_v3; TYPE_2__ public_v2; TYPE_1__ public_v1; } ;
struct symt_compiland {int dummy; } ;
struct msc_debug_info {TYPE_11__* module; } ;
struct TYPE_13__ {void* sortlist_valid; } ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  void* BOOL ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int SYMOPT_NO_PUBLICS ; 
 int /*<<< orphan*/  SYMTYPE_FUNCTION ; 
#define  S_DATAREF_V1 147 
#define  S_GDATA_V1 146 
#define  S_GDATA_V2 145 
#define  S_GDATA_V3 144 
#define  S_GTHREAD_V1 143 
#define  S_GTHREAD_V2 142 
#define  S_GTHREAD_V3 141 
#define  S_LDATA_V1 140 
#define  S_LDATA_V2 139 
#define  S_LDATA_V3 138 
#define  S_LPROCREF_V1 137 
#define  S_LTHREAD_V1 136 
#define  S_LTHREAD_V2 135 
#define  S_LTHREAD_V3 134 
#define  S_PROCREF_V1 133 
#define  S_PUB_FUNC1_V3 132 
#define  S_PUB_FUNC2_V3 131 
#define  S_PUB_V1 130 
#define  S_PUB_V2 129 
#define  S_PUB_V3 128 
 void* TRUE ; 
 int /*<<< orphan*/  codeview_add_variable (struct msc_debug_info const*,struct symt_compiland*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void*,void*) ; 
 int /*<<< orphan*/  codeview_get_address (struct msc_debug_info const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dbghelp_options ; 
 int /*<<< orphan*/  symt_new_public (TYPE_11__*,struct symt_compiland*,int /*<<< orphan*/ ,int,int,...) ; 
 int /*<<< orphan*/  terminate_string (int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL codeview_snarf_public(const struct msc_debug_info* msc_dbg, const BYTE* root,
                                  int offset, int size)

{
    int                                 i, length;
    struct symt_compiland*              compiland = NULL;

    /*
     * Loop over the different types of records and whenever we
     * find something we are interested in, record it and move on.
     */
    for (i = offset; i < size; i += length)
    {
        const union codeview_symbol* sym = (const union codeview_symbol*)(root + i);
        length = sym->generic.len + 2;
        if (i + length > size) break;
        if (!sym->generic.id || length < 4) break;
        if (length & 3) FIXME("unpadded len %u\n", length);

        switch (sym->generic.id)
        {
	case S_PUB_V1:
            if (!(dbghelp_options & SYMOPT_NO_PUBLICS))
            {
                symt_new_public(msc_dbg->module, compiland,
                                terminate_string(&sym->public_v1.p_name),
                                sym->public_v1.symtype == SYMTYPE_FUNCTION,
                                codeview_get_address(msc_dbg, sym->public_v1.segment, sym->public_v1.offset), 1);
            }
            break;
	case S_PUB_V2:
            if (!(dbghelp_options & SYMOPT_NO_PUBLICS))
            {
                symt_new_public(msc_dbg->module, compiland,
                                terminate_string(&sym->public_v2.p_name),
                                sym->public_v3.symtype == SYMTYPE_FUNCTION,
                                codeview_get_address(msc_dbg, sym->public_v2.segment, sym->public_v2.offset), 1);
            }
	    break;

        case S_PUB_V3:
            if (!(dbghelp_options & SYMOPT_NO_PUBLICS))
            {
                symt_new_public(msc_dbg->module, compiland,
                                sym->public_v3.name,
                                sym->public_v3.symtype == SYMTYPE_FUNCTION,
                                codeview_get_address(msc_dbg, sym->public_v3.segment, sym->public_v3.offset), 1);
            }
            break;
        case S_PUB_FUNC1_V3:
        case S_PUB_FUNC2_V3: /* using a data_v3 isn't what we'd expect */
#if 0
            /* FIXME: this is plain wrong (from a simple test) */
            if (!(dbghelp_options & SYMOPT_NO_PUBLICS))
            {
                symt_new_public(msc_dbg->module, compiland,
                                sym->data_v3.name,
                                codeview_get_address(msc_dbg, sym->data_v3.segment, sym->data_v3.offset), 1);
            }
#endif
            break;
        /*
         * Global and local data symbols.  We don't associate these
         * with any given source file.
         */
	case S_GDATA_V1:
	case S_LDATA_V1:
            codeview_add_variable(msc_dbg, compiland, terminate_string(&sym->data_v1.p_name),
                                  sym->data_v1.segment, sym->data_v1.offset, sym->data_v1.symtype,
                                  sym->generic.id == S_LDATA_V1, FALSE, FALSE);
	    break;
	case S_GDATA_V2:
	case S_LDATA_V2:
            codeview_add_variable(msc_dbg, compiland, terminate_string(&sym->data_v2.p_name),
                                  sym->data_v2.segment, sym->data_v2.offset, sym->data_v2.symtype,
                                  sym->generic.id == S_LDATA_V2, FALSE, FALSE);
	    break;
	case S_GDATA_V3:
	case S_LDATA_V3:
            codeview_add_variable(msc_dbg, compiland, sym->data_v3.name,
                                  sym->data_v3.segment, sym->data_v3.offset, sym->data_v3.symtype,
                                  sym->generic.id == S_LDATA_V3, FALSE, FALSE);
	    break;

        /* variables with thread storage */
	case S_GTHREAD_V1:
	case S_LTHREAD_V1:
            codeview_add_variable(msc_dbg, compiland, terminate_string(&sym->thread_v1.p_name),
                                  sym->thread_v1.segment, sym->thread_v1.offset, sym->thread_v1.symtype,
                                  sym->generic.id == S_LTHREAD_V1, TRUE, FALSE);
	    break;
	case S_GTHREAD_V2:
	case S_LTHREAD_V2:
            codeview_add_variable(msc_dbg, compiland, terminate_string(&sym->thread_v2.p_name),
                                  sym->thread_v2.segment, sym->thread_v2.offset, sym->thread_v2.symtype,
                                  sym->generic.id == S_LTHREAD_V2, TRUE, FALSE);
	    break;
	case S_GTHREAD_V3:
	case S_LTHREAD_V3:
            codeview_add_variable(msc_dbg, compiland, sym->thread_v3.name,
                                  sym->thread_v3.segment, sym->thread_v3.offset, sym->thread_v3.symtype,
                                  sym->generic.id == S_LTHREAD_V3, TRUE, FALSE);
	    break;

        /*
         * These are special, in that they are always followed by an
         * additional length-prefixed string which is *not* included
         * into the symbol length count.  We need to skip it.
         */
	case S_PROCREF_V1:
	case S_DATAREF_V1:
	case S_LPROCREF_V1:
            length += (((const char*)sym)[length] + 1 + 3) & ~3;
            break;
        }
        msc_dbg->module->sortlist_valid = TRUE;
    }
    msc_dbg->module->sortlist_valid = FALSE;
    return TRUE;
}