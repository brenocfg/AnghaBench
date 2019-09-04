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
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_20__ {TYPE_1__* title; } ;
typedef  TYPE_7__ tt_srpt_t ;
struct TYPE_21__ {int pgcn; int pgn; } ;
typedef  TYPE_8__ ptt_info_t ;
struct TYPE_22__ {unsigned int* program_map; int nr_of_programs; TYPE_6__* cell_playback; } ;
typedef  TYPE_9__ pgc_t ;
struct TYPE_13__ {TYPE_5__* vts_pgcit; TYPE_3__* vts_ptt_srpt; } ;
typedef  TYPE_10__ ifo_handle_t ;
struct TYPE_19__ {scalar_t__ block_type; scalar_t__ block_mode; int /*<<< orphan*/  playback_time; } ;
struct TYPE_18__ {TYPE_4__* pgci_srp; } ;
struct TYPE_17__ {TYPE_9__* pgc; } ;
struct TYPE_16__ {TYPE_2__* title; } ;
struct TYPE_15__ {int nr_of_ptts; TYPE_8__* ptt; } ;
struct TYPE_14__ {int vts_ttn; } ;

/* Variables and functions */
 scalar_t__ BLOCK_MODE_FIRST_CELL ; 
 scalar_t__ BLOCK_TYPE_ANGLE_BLOCK ; 
 scalar_t__ mp_dvdtimetomsec (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_chapter_time(ifo_handle_t *vts_file, tt_srpt_t *tt_srpt, int title_no, double *p)
{
    unsigned int i, cell, last_cell;
    unsigned int t=0;
    ptt_info_t *ptt;
    pgc_t *pgc;

    title_no = tt_srpt->title[title_no].vts_ttn - 1;
    if(vts_file->vts_ptt_srpt->title[title_no].nr_of_ptts < 2)
       return 0;
    ptt = vts_file->vts_ptt_srpt->title[title_no].ptt;

    int cur = 0;
    for(i=0; i<vts_file->vts_ptt_srpt->title[title_no].nr_of_ptts; i++)
    {
        pgc = vts_file->vts_pgcit->pgci_srp[ptt[i].pgcn-1].pgc;
        cell = pgc->program_map[ptt[i].pgn-1]; //here the cell is 1-based
        if(ptt[i].pgn<pgc->nr_of_programs)
            last_cell = pgc->program_map[ptt[i].pgn];
        else
            last_cell = 0;
        while (cell < last_cell) {
            if(!(pgc->cell_playback[cell-1].block_type == BLOCK_TYPE_ANGLE_BLOCK &&
                 pgc->cell_playback[cell-1].block_mode != BLOCK_MODE_FIRST_CELL)
            ) {
                if (cur == *p) {
                    *p = t / 1000.0;
                    return 1;
                }
                t += mp_dvdtimetomsec(&pgc->cell_playback[cell-1].playback_time);
                cur++;
            }
            cell++;
        }
    }
    return 0;
}