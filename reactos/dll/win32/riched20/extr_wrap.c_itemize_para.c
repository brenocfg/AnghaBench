#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_38__   TYPE_9__ ;
typedef  struct TYPE_37__   TYPE_8__ ;
typedef  struct TYPE_36__   TYPE_7__ ;
typedef  struct TYPE_35__   TYPE_6__ ;
typedef  struct TYPE_34__   TYPE_5__ ;
typedef  struct TYPE_33__   TYPE_4__ ;
typedef  struct TYPE_32__   TYPE_3__ ;
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_1__ ;
typedef  struct TYPE_29__   TYPE_13__ ;
typedef  struct TYPE_28__   TYPE_12__ ;
typedef  struct TYPE_27__   TYPE_11__ ;
typedef  struct TYPE_26__   TYPE_10__ ;

/* Type definitions */
struct TYPE_32__ {int /*<<< orphan*/  uBidiLevel; } ;
struct TYPE_33__ {int /*<<< orphan*/  fLogicalOrder; TYPE_3__ s; int /*<<< orphan*/  fRTL; } ;
struct TYPE_38__ {int nCharOfs; int nFlags; int len; TYPE_4__ script_analysis; } ;
struct TYPE_37__ {int /*<<< orphan*/  member_10; int /*<<< orphan*/  member_9; int /*<<< orphan*/  member_8; int /*<<< orphan*/  member_7; int /*<<< orphan*/  member_6; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_36__ {int iCharPos; TYPE_4__ a; } ;
struct TYPE_35__ {int uBidiLevel; int /*<<< orphan*/  member_10; int /*<<< orphan*/  member_9; int /*<<< orphan*/  member_8; int /*<<< orphan*/  member_7; int /*<<< orphan*/  member_6; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_30__ {int dwMask; int wEffects; } ;
struct TYPE_26__ {int /*<<< orphan*/  nFlags; TYPE_11__* next_para; TYPE_2__* text; TYPE_1__ fmt; } ;
struct TYPE_34__ {TYPE_9__ run; TYPE_10__ para; } ;
struct TYPE_31__ {int nLen; int /*<<< orphan*/  szData; } ;
struct TYPE_29__ {int /*<<< orphan*/  editor; } ;
struct TYPE_28__ {int member_2; TYPE_11__* member_1; TYPE_11__* member_0; } ;
struct TYPE_27__ {scalar_t__ type; TYPE_5__ member; struct TYPE_27__* next; } ;
typedef  TYPE_6__ SCRIPT_STATE ;
typedef  TYPE_7__ SCRIPT_ITEM ;
typedef  TYPE_8__ SCRIPT_CONTROL ;
typedef  TYPE_9__ ME_Run ;
typedef  TYPE_10__ ME_Paragraph ;
typedef  TYPE_11__ ME_DisplayItem ;
typedef  TYPE_12__ ME_Cursor ;
typedef  TYPE_13__ ME_Context ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_7__*) ; 
 scalar_t__ E_OUTOFMEMORY ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LANG_USER_DEFAULT ; 
 int /*<<< orphan*/  MEPF_COMPLEX ; 
 int MERF_ENDPARA ; 
 int /*<<< orphan*/  ME_SplitRunSimple (int /*<<< orphan*/ ,TYPE_12__*) ; 
 int PFE_RTLPARA ; 
 int PFM_RTLPARA ; 
 scalar_t__ ScriptItemize (int /*<<< orphan*/ ,int,int,TYPE_8__*,TYPE_6__*,TYPE_7__*,int*) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 scalar_t__ TRACE_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  debugstr_run (TYPE_9__*) ; 
 scalar_t__ diParagraph ; 
 scalar_t__ diRun ; 
 TYPE_7__* heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (TYPE_7__*) ; 
 TYPE_7__* heap_realloc (TYPE_7__*,int) ; 
 int /*<<< orphan*/  richedit ; 

__attribute__((used)) static HRESULT itemize_para( ME_Context *c, ME_DisplayItem *p )
{
    ME_Paragraph *para = &p->member.para;
    ME_Run *run;
    ME_DisplayItem *di;
    SCRIPT_ITEM buf[16], *items = buf;
    int items_passed = ARRAY_SIZE( buf ), num_items, cur_item;
    SCRIPT_CONTROL control = { LANG_USER_DEFAULT, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
                               FALSE, FALSE, 0 };
    SCRIPT_STATE state = { 0, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, 0, 0 };
    HRESULT hr;

    assert( p->type == diParagraph );

    if (para->fmt.dwMask & PFM_RTLPARA && para->fmt.wEffects & PFE_RTLPARA)
        state.uBidiLevel = 1;

    TRACE( "Base embedding level %d\n", state.uBidiLevel );

    while (1)
    {
        hr = ScriptItemize( para->text->szData, para->text->nLen, items_passed, &control,
                            &state, items, &num_items );
        if (hr != E_OUTOFMEMORY) break; /* may not be enough items if hr == E_OUTOFMEMORY */
        if (items_passed > para->text->nLen + 1) break; /* something else has gone wrong */
        items_passed *= 2;
        if (items == buf)
            items = heap_alloc( items_passed * sizeof( *items ) );
        else
            items = heap_realloc( items, items_passed * sizeof( *items ) );
        if (!items) break;
    }
    if (FAILED( hr )) goto end;

    if (TRACE_ON( richedit ))
    {
        TRACE( "got items:\n" );
        for (cur_item = 0; cur_item < num_items; cur_item++)
        {
            TRACE( "\t%d - %d RTL %d bidi level %d\n", items[cur_item].iCharPos, items[cur_item+1].iCharPos - 1,
                   items[cur_item].a.fRTL, items[cur_item].a.s.uBidiLevel );
        }

        TRACE( "before splitting runs into ranges\n" );
        for (di = p->next; di != p->member.para.next_para; di = di->next)
        {
            if (di->type != diRun) continue;
            TRACE( "\t%d: %s\n", di->member.run.nCharOfs, debugstr_run( &di->member.run ) );
        }
    }

    /* split runs into ranges at item boundaries */
    for (di = p->next, cur_item = 0; di != p->member.para.next_para; di = di->next)
    {
        if (di->type != diRun) continue;
        run = &di->member.run;

        if (run->nCharOfs == items[cur_item+1].iCharPos) cur_item++;

        items[cur_item].a.fLogicalOrder = TRUE;
        run->script_analysis = items[cur_item].a;

        if (run->nFlags & MERF_ENDPARA) break; /* don't split eop runs */

        if (run->nCharOfs + run->len > items[cur_item+1].iCharPos)
        {
            ME_Cursor cursor = {p, di, items[cur_item+1].iCharPos - run->nCharOfs};
            ME_SplitRunSimple( c->editor, &cursor );
        }
    }

    if (TRACE_ON( richedit ))
    {
        TRACE( "after splitting into ranges\n" );
        for (di = p->next; di != p->member.para.next_para; di = di->next)
        {
            if (di->type != diRun) continue;
            TRACE( "\t%d: %s\n", di->member.run.nCharOfs, debugstr_run( &di->member.run ) );
        }
    }

    para->nFlags |= MEPF_COMPLEX;

end:
    if (items != buf) heap_free( items );
    return hr;
}