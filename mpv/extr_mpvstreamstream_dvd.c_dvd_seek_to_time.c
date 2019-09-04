#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
struct TYPE_24__ {TYPE_1__* tmap; } ;
typedef  TYPE_7__ vts_tmapt_t ;
struct TYPE_25__ {TYPE_10__* priv; } ;
typedef  TYPE_8__ stream_t ;
typedef  int int64_t ;
struct TYPE_26__ {TYPE_6__* vts_vobu_admap; TYPE_7__* vts_tmapt; } ;
typedef  TYPE_9__ ifo_handle_t ;
typedef  int /*<<< orphan*/  dvd_time_t ;
struct TYPE_21__ {int /*<<< orphan*/  c_eltm; } ;
struct TYPE_22__ {TYPE_4__ dsi_gi; } ;
struct TYPE_17__ {unsigned int cur_pgc_idx; TYPE_5__ dsi_pack; TYPE_3__* cur_pgc; int /*<<< orphan*/  cur_title; int /*<<< orphan*/  tt_srpt; int /*<<< orphan*/  vts_file; } ;
typedef  TYPE_10__ dvd_priv_t ;
struct TYPE_23__ {int last_byte; unsigned int* vobu_start_sectors; } ;
struct TYPE_20__ {unsigned int nr_of_cells; TYPE_2__* cell_playback; } ;
struct TYPE_19__ {unsigned int first_sector; unsigned int last_sector; } ;
struct TYPE_18__ {unsigned int tmu; unsigned int nr_of_entries; int* map_ent; } ;

/* Variables and functions */
 int VOBU_ADMAP_SIZE ; 
 int /*<<< orphan*/  do_seek (TYPE_8__*,int) ; 
 double dvd_get_current_time (TYPE_8__*,int) ; 
 scalar_t__ dvd_read_sector (TYPE_8__*,TYPE_10__*,char*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int mp_dvdtimetomsec (int /*<<< orphan*/ *) ; 
 scalar_t__ mp_get_titleset_length (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dvd_seek_to_time(stream_t *stream, ifo_handle_t *vts_file, double sec)
{
    unsigned int i, j, k, timeunit, ac_time, tmap_sector=0, cell_sector=0, vobu_sector=0;
    int t=0;
    double tm, duration;
    int64_t pos = -1;
    dvd_priv_t *d = stream->priv;
    vts_tmapt_t *vts_tmapt = vts_file->vts_tmapt;

    if(!vts_file->vts_tmapt || sec < 0)
        return 0;

    duration = (double) mp_get_titleset_length(d->vts_file, d->tt_srpt, d->cur_title) / 1000.0f;
    if(sec > duration)
      return 0;

    i=d->cur_pgc_idx;
    timeunit = vts_tmapt->tmap[i].tmu;
    for(j = 0; j < vts_tmapt->tmap[i].nr_of_entries; j++) {
      ac_time = timeunit * (j + 1);
      if(ac_time >= sec)
        break;
      tmap_sector = vts_tmapt->tmap[i].map_ent[j] & 0x7fffffff;
    }
    //search enclosing cell
    for(i=0; i<d->cur_pgc->nr_of_cells; i++) {
      if(tmap_sector >= d->cur_pgc->cell_playback[i].first_sector && tmap_sector <= d->cur_pgc->cell_playback[i].last_sector) {
        cell_sector = d->cur_pgc->cell_playback[i].first_sector;
        break;
      }
    }

    pos = ((int64_t)cell_sector)<<11;
    do_seek(stream, pos);
    do {
      char buf[2048];
      if (dvd_read_sector(stream, stream->priv, buf) < 0) // skip
          break;
      t = mp_dvdtimetomsec(&d->dsi_pack.dsi_gi.c_eltm);
    } while(!t);
    tm = dvd_get_current_time(stream, -1);

    pos = ((int64_t)tmap_sector)<<11;
    do_seek(stream, pos);
    //now get current time in terms of the cell+cell time offset
    memset(&d->dsi_pack.dsi_gi.c_eltm, 0, sizeof(dvd_time_t));
    while(tm <= sec) {
        char buf[2048];
        if (dvd_read_sector(stream, stream->priv, buf) < 0) // skip
            break;
        pos += 2048;
        tm = dvd_get_current_time(stream, -1);
    };
    tmap_sector = pos >> 11;

    //search closest VOBU sector
    k=(vts_file->vts_vobu_admap->last_byte + 1 - VOBU_ADMAP_SIZE)/4; //entries in the vobu admap
    for(i=1; i<k; i++) {
      if(vts_file->vts_vobu_admap->vobu_start_sectors[i] > tmap_sector)
        break;
    }
    vobu_sector = vts_file->vts_vobu_admap->vobu_start_sectors[i-1];
    pos = ((int64_t)vobu_sector) << 11;
    do_seek(stream, pos);

    return 1;
}