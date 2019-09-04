#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  stream_t ;
struct TYPE_6__ {int packs_left; int cur_pack; int cell_last_pack; size_t cur_cell; int angle_seek; TYPE_1__* cur_pgc; } ;
typedef  TYPE_2__ dvd_priv_t ;
struct TYPE_7__ {int first_sector; scalar_t__ block_type; scalar_t__ block_mode; int last_sector; } ;
typedef  TYPE_3__ cell_playback_t ;
struct TYPE_5__ {size_t nr_of_cells; TYPE_3__* cell_playback; } ;

/* Variables and functions */
 scalar_t__ BLOCK_MODE_FIRST_CELL ; 
 scalar_t__ BLOCK_TYPE_ANGLE_BLOCK ; 
 int /*<<< orphan*/  MP_VERBOSE (int /*<<< orphan*/ *,char*,int,size_t,scalar_t__,int) ; 

__attribute__((used)) static void dvd_seek(stream_t *stream, dvd_priv_t *d, int pos)
{
  d->packs_left=-1;
  d->cur_pack=pos;

  // check if we stay in current cell (speedup things, and avoid angle skip)
  if(d->cur_pack>d->cell_last_pack ||
     d->cur_pack<d->cur_pgc->cell_playback[ d->cur_cell ].first_sector) {

    // ok, cell change, find the right cell!
    cell_playback_t *cell;
    for(d->cur_cell=0; d->cur_cell < d->cur_pgc->nr_of_cells; d->cur_cell++) {
      cell = &(d->cur_pgc->cell_playback[d->cur_cell]);
      if(cell->block_type == BLOCK_TYPE_ANGLE_BLOCK && cell->block_mode != BLOCK_MODE_FIRST_CELL)
        continue;
      d->cell_last_pack=cell->last_sector;
      if(d->cur_pack<cell->first_sector) {
        d->cur_pack=cell->first_sector;
        break;
      }
      if(d->cur_pack<=d->cell_last_pack) break; // ok, we find it! :)
    }
  }

  MP_VERBOSE(stream, "DVD Seek! lba=0x%X  cell=%d  packs: 0x%X-0x%X  \n",
    d->cur_pack,d->cur_cell,d->cur_pgc->cell_playback[ d->cur_cell ].first_sector,d->cell_last_pack);

  // if we're in interleaved multi-angle cell, find the right angle chain!
  // (read Navi block, and use the seamless angle jump table)
  d->angle_seek=1;
}