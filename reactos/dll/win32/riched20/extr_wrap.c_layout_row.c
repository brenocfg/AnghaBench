#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int x; } ;
struct TYPE_11__ {int /*<<< orphan*/  uBidiLevel; } ;
struct TYPE_12__ {TYPE_1__ s; } ;
struct TYPE_16__ {int nFlags; int nWidth; TYPE_5__ pt; TYPE_4__* para; TYPE_2__ script_analysis; } ;
struct TYPE_17__ {TYPE_6__ run; } ;
struct TYPE_18__ {scalar_t__ type; TYPE_7__ member; struct TYPE_18__* next; struct TYPE_18__* prev; } ;
struct TYPE_13__ {int x; } ;
struct TYPE_14__ {TYPE_3__ pt; } ;
typedef  TYPE_8__ ME_DisplayItem ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int FALSE ; 
 int MERF_ENDPARA ; 
 int MERF_WHITESPACE ; 
 int /*<<< orphan*/  ScriptLayout (int,int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  TRACE (char*,int,...) ; 
 scalar_t__ diRun ; 
 int* heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (int*) ; 

__attribute__((used)) static void layout_row( ME_DisplayItem *start, const ME_DisplayItem *end )
{
    ME_DisplayItem *p;
    int i, num_runs = 0;
    int buf[16 * 5]; /* 5 arrays - 4 of int & 1 of BYTE, alloc space for 5 of ints */
    int *vis_to_log = buf, *log_to_vis, *widths, *pos;
    BYTE *levels;
    BOOL found_black = FALSE;

    for (p = end->prev; p != start->prev; p = p->prev)
    {
        if (p->type == diRun)
        {
            if (!found_black) found_black = !(p->member.run.nFlags & (MERF_WHITESPACE | MERF_ENDPARA));
            if (found_black) num_runs++;
        }
    }

    TRACE("%d runs\n", num_runs);
    if (!num_runs) return;

    if (num_runs > ARRAY_SIZE( buf ) / 5)
        vis_to_log = heap_alloc( num_runs * sizeof(int) * 5 );

    log_to_vis = vis_to_log + num_runs;
    widths = vis_to_log + 2 * num_runs;
    pos = vis_to_log + 3 * num_runs;
    levels = (BYTE*)(vis_to_log + 4 * num_runs);

    for (i = 0, p = start; i < num_runs; p = p->next)
    {
        if (p->type == diRun)
        {
            levels[i] = p->member.run.script_analysis.s.uBidiLevel;
            widths[i] = p->member.run.nWidth;
            TRACE( "%d: level %d width %d\n", i, levels[i], widths[i] );
            i++;
        }
    }

    ScriptLayout( num_runs, levels, vis_to_log, log_to_vis );

    pos[0] = start->member.run.para->pt.x;
    for (i = 1; i < num_runs; i++)
        pos[i] = pos[i - 1] + widths[ vis_to_log[ i - 1 ] ];

    for (i = 0, p = start; i < num_runs; p = p->next)
    {
        if (p->type == diRun)
        {
            p->member.run.pt.x = pos[ log_to_vis[ i ] ];
            TRACE( "%d: x = %d\n", i, p->member.run.pt.x );
            i++;
        }
    }

    if (vis_to_log != buf) heap_free( vis_to_log );
}