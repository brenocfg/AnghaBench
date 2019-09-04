#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_6__* priv; } ;
typedef  TYPE_5__ stream_t ;
struct TYPE_10__ {int /*<<< orphan*/  c_eltm; } ;
struct TYPE_11__ {TYPE_3__ dsi_gi; } ;
struct TYPE_13__ {int cur_cell; TYPE_4__ dsi_pack; scalar_t__* cell_times_table; TYPE_2__* cur_pgc; } ;
typedef  TYPE_6__ dvd_priv_t ;
struct TYPE_9__ {TYPE_1__* cell_playback; } ;
struct TYPE_8__ {scalar_t__ block_type; scalar_t__ block_mode; } ;

/* Variables and functions */
 scalar_t__ BLOCK_MODE_FIRST_CELL ; 
 scalar_t__ BLOCK_TYPE_ANGLE_BLOCK ; 
 scalar_t__ mp_dvdtimetomsec (int /*<<< orphan*/ *) ; 

__attribute__((used)) static double dvd_get_current_time(stream_t *stream, int cell)
{
    int i, tm;
    dvd_priv_t *d = stream->priv;

    tm=0;
    if(cell < 0) cell=d->cur_cell;
    for(i=0; i<cell; i++) {
        if(d->cur_pgc->cell_playback[i].block_type == BLOCK_TYPE_ANGLE_BLOCK &&
           d->cur_pgc->cell_playback[i].block_mode != BLOCK_MODE_FIRST_CELL
        )
          continue;
        tm += d->cell_times_table[i];
    }
    tm += mp_dvdtimetomsec(&d->dsi_pack.dsi_gi.c_eltm);

    return (double)tm/1000.0;
}