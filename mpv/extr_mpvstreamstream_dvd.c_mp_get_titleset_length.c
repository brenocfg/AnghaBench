#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {TYPE_1__* title; } ;
typedef  TYPE_8__ tt_srpt_t ;
struct TYPE_20__ {TYPE_7__* vts_pgcit; TYPE_4__* vts_ptt_srpt; scalar_t__ vtsi_mat; } ;
typedef  TYPE_9__ ifo_handle_t ;
struct TYPE_18__ {TYPE_6__* pgci_srp; } ;
struct TYPE_17__ {TYPE_5__* pgc; } ;
struct TYPE_16__ {int /*<<< orphan*/  playback_time; } ;
struct TYPE_15__ {TYPE_3__* title; } ;
struct TYPE_14__ {TYPE_2__* ptt; } ;
struct TYPE_13__ {int pgcn; } ;
struct TYPE_12__ {int vts_ttn; } ;

/* Variables and functions */
 int mp_dvdtimetomsec (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mp_get_titleset_length(ifo_handle_t *vts_file, tt_srpt_t *tt_srpt, int title_no)
{
    int vts_ttn;  ///< title number within video title set
    int pgc_no;   ///< program chain number
    int msec;     ///< time length in milliseconds

    msec=0;
    if(!vts_file || !tt_srpt)
        return 0;

    if(vts_file->vtsi_mat && vts_file->vts_pgcit)
    {
            vts_ttn = tt_srpt->title[title_no].vts_ttn - 1;
            pgc_no = vts_file->vts_ptt_srpt->title[vts_ttn].ptt[0].pgcn - 1;
            msec = mp_dvdtimetomsec(&vts_file->vts_pgcit->pgci_srp[pgc_no].pgc->playback_time);
    }
    return msec;
}