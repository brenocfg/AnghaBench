#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int nr_of_srpts; TYPE_3__* title; } ;
typedef  TYPE_4__ tt_srpt_t ;
struct TYPE_12__ {TYPE_2__* vts_ptt_srpt; } ;
typedef  TYPE_5__ ifo_handle_t ;
struct TYPE_10__ {int vts_ttn; } ;
struct TYPE_9__ {int nr_of_srpts; TYPE_1__* title; } ;
struct TYPE_8__ {int nr_of_ptts; } ;

/* Variables and functions */

__attribute__((used)) static int get_num_chapter(ifo_handle_t *vts_file, tt_srpt_t *tt_srpt, int title_no)
{
    if(!vts_file || !tt_srpt)
       return 0;

    if(title_no < 0 || title_no >= tt_srpt->nr_of_srpts)
       return 0;

    // map global title to vts title
    title_no = tt_srpt->title[title_no].vts_ttn - 1;

    if(title_no < 0 || title_no >= vts_file->vts_ptt_srpt->nr_of_srpts)
       return 0;

    return vts_file->vts_ptt_srpt->title[title_no].nr_of_ptts;
}